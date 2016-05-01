//
//  Evolution.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Evolution.h"

Evolution* Evolution::m_pInstance = NULL;

Evolution::Evolution() {//generation num and population num;
	crossCoverRate = 0.3;
	mutationRate = 0.1;
	generationNum = 50; //50
	generatePopulation(100);//200 need to be divede by 4
	currentPairNum = 0;
    evolutionEnd = false;
}
Evolution::~Evolution() {}
void Evolution::generatePopulation(int popuNum) {
    fstream f("/Users/isware/Documents/Cocos2D-x/workspace/Animal/out1.txt");
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
            int upperBound, lowerBound;
            
            if(i == 0){
                lowerBound = 1;
                upperBound = population.at(genePos).getGene().at(i+1);
            }
            else if (i>0 && i<7){
                lowerBound = population.at(genePos).getGene().at(i-1);
                upperBound = population.at(genePos).getGene().at(i+1);
            }
            else if (i == 7){
                lowerBound = population.at(genePos).getGene().at(i-1);
                upperBound = 200;
            }
            else if (i == 8){
                lowerBound = population.at(genePos).getGene().at(i+1);
                upperBound = 200;
            }
            else if (i > 8 && i < 17){
                lowerBound = population.at(genePos).getGene().at(i+1);
                upperBound = population.at(genePos).getGene().at(i-1);
            }
            else if (i == 17){
                lowerBound = 1;
                upperBound = population.at(genePos).getGene().at(i-1);
            }
            else if (i == 18){
                lowerBound = 1;
                upperBound = 11;
            }
            else{
                lowerBound = 0;
                upperBound = 10;
            }
        
            if(lowerBound>upperBound){
                float temp = lowerBound;
                lowerBound = upperBound;
                upperBound = temp;
            }
           
            
            float a =(float)(rand()%(upperBound-lowerBound+1)+lowerBound);
            
            population.at(genePos).updateGene(i, a);
        }
	}
}
void Evolution::crossCover(int genePos1, int genePos2) {
     cout<<"I am crosscover "<<genePos1<<" and "<<genePos2<<endl;
	for (int i = 0; i<population[0].getGene().size(); i++) {
		float a = (float)rand() / RAND_MAX;
		if (a<crossCoverRate) {
            
			float temp = population.at(genePos1).getGene().at(i);
            population.at(genePos1).updateGene(i,population.at(genePos2).getGene().at(i));
            population.at(genePos2).updateGene(i, temp);
            //float a =(population.at(genePos1).getGene().at(i)+population.at(genePos2).getGene().at(i))/2;
            //population.at(genePos1).updateGene(i, a);
            //population.at(genePos2).updateGene(i, a);
            


		}
	}
}
void Evolution::select() {
    cout<<"I am select"<<endl;
	if (generationNum>0) {
		vector<Gene> temp;

		for (int i = 0; i<population.size(); i++) { //get the winner gene
			if (population.at(i).winState == 1) {
				temp.push_back(population.at(i));
			}
		}
        population.clear();
		population = temp;

		for (int j = 0; j< population.size() / 2; j++) {//do crosscover
			crossCover(j, population.size() - 1 - j);
		}

		for (int k = 0; k<population.size(); k++) {  //do mutation
			mutation(k);
		}

		for (int l = 0; l< temp.size(); l++) { //add unchanged gene to population
			population.push_back(temp.at(l));
		}
	}
	generationNum--;
}

int Evolution::getGenerationNum() {
	return generationNum;
}

void Evolution::storePopulationGenes() {
	int size1 = population.size();
	int size2 = population[0].getGene().size();
	ofstream outfile("/Users/isware/Documents/Cocos2D-x/workspace/Animal/out1.txt");
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
	ifstream infile("/Users/isware/Documents/Cocos2D-x/workspace/Animal/out1.txt");
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
				break;
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