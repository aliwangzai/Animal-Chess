//
//  Evolution.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Evolution.h"
#include <random>
#include <time.h>

Evolution* Evolution::m_pInstance = NULL;

Evolution::Evolution() {//generation num and population num;
	crossCoverRate = 0.2;
	mutationRate = 0.1;
	generationNum = 20;
	generatePopulation(20);
    evolutionEnd = false;
    p1 = 0;
    p2 = 1;
}
Evolution::~Evolution() {}
void Evolution::generatePopulation(int popuNum) {
    fstream f("out1.txt");
    if(f.fail()){
        cout<<"file not exist!"<<endl;
        for (int i = 0; i < popuNum; i++) {
            Gene newgene = Gene::Gene();
            newgene.generateRandomGene();
            population.push_back(newgene);
        //newgene.printGene();
        }
    }
    else{
        cout<<"load genes from exist file"<<endl;
        loadPopulationGenes();
    }
	storePopulationGenes();
}
void Evolution::mutation(int genePos) {

	for (int i = 0; i<population[0].getGene().size(); i++) {
        float c = (float)rand() / RAND_MAX;
        if (c<mutationRate){
            float upperBound, lowerBound;
            if (i >= 2){
                lowerBound = 1;
                upperBound = 200;
            }
            else if (i == 0){
                lowerBound = 0;
                upperBound = 10;
            }
            else{
                lowerBound = 1;
                upperBound = 11;
            }

            std::default_random_engine generator(time(0));
			std::normal_distribution<float> distribution(population[genePos].getGene().at(i), 5);
			float newVal = distribution(generator);
            population.at(genePos).updateGene(i, newVal);
        }
	}

}
void Evolution::crossCover(int genePos1, int genePos2) {
     cout<<"I am crosscovering "<<genePos1<<" and "<<genePos2<<endl;
	for (int i = 0; i<population[0].getGene().size(); i++) {
		float a = (float)rand() / RAND_MAX;
		if (a<crossCoverRate) {
			auto a = population[genePos1].getGene().at(i);
			auto b = population[genePos2].getGene().at(i);
			population.at(genePos1).updateGene(i, b);
			population.at(genePos2).updateGene(i, a);
		}
	}
}
void Evolution::select() {
	if (generationNum>0) {
		//select best 10 and store into temp
		sort(population.begin(), population.end(), [](const Gene& a, const Gene& b) {return 1.0*a.winGames/(a.winGames + a.drawGames+a.loseGames) > 1.0*b.winGames/(b.winGames+b.loseGames+b.drawGames); });
		auto size_pop = population.size();
		for (auto i = 0; i < size_pop;i++) {
			auto p = population[i];
			printf("[%d]: %d %d %d\n", i, p.winGames, p.loseGames, p.drawGames);
		}
		auto temp = vector<Gene>(population.begin(), population.begin() + 5);


		// copy 3 times temp
		for (int i = 0; i < 3; i++) {
			for (auto t : temp) {
				t.drawGames = 0; t.loseGames = 0; t.winGames = 0;
				population.push_back(t);
			}
		}

		size_pop = population.size();
		for (int j = 0; j< population.size() / 2; j++) {//do crosscover
			auto c1 = rand() % size_pop;
			auto c2 = rand() % size_pop;
			crossCover(c1, c2);
		}
		for (int k = 0; k<size_pop; k++) {  //do mutation
			mutation(k);
		}
		
		for (auto t : temp) 
			population.push_back(t);
		
	}
	generationNum--;
}

int Evolution::getGenerationNum() {
	return generationNum;
}

void Evolution::storePopulationGenes() {
	size_t size1 = population.size();
	size_t size2 = population[0].getGene().size();
	ofstream outfile("out1.txt");
	if (!outfile)
		cout << "cant open out file" << endl;
	else {
		for (int i = 0; i< size1; i++) {
			for (int j = 0; j< size2; j++) {
				outfile << population.at(i).getGene().at(j) << " ";
			}
			outfile << endl;
		}
		cout << "write " << size1 << " genes to file" << endl;
		outfile.close();
	}
}
void Evolution::loadPopulationGenes() {
	int numwrite = 0;
	ifstream infile("out1.txt");
	if (!infile)
		cout << "cant open infile " << endl;
	else {
		char buffer[1024];
		population.clear();
		Gene n_gene = Gene();
		while (!infile.eof()) {
			infile.getline(buffer, 1024);
			string s = buffer;
			string word;
			vector<float> sepBySpaceStr;
			stringstream ss(s);
			if (s == "")
				continue;
			while (ss >> word)
				sepBySpaceStr.push_back(atof(word.c_str()));
			n_gene.setGene(sepBySpaceStr);
			population.push_back(n_gene);
			numwrite++;
		}
	}
	cout << "write in " << numwrite << " genes" << endl;
	infile.close();
}