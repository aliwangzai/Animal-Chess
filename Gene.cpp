
//
//  Gene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Gene.h"

Gene::Gene() { winState = 0; }
Gene::~Gene() {}

void Gene::generateRandomGene() {
    vector<float> temp;
    for(int i  = 0 ; i<20;i++){
        temp.push_back((float)(rand() % 401)+1);
    }
    std::sort(temp.begin(),temp.begin()+8);
    std::sort(temp.begin()+8,temp.end());
    std::reverse(temp.begin()+8, temp.end());

	for (int i = 0; i<20; i++) {
        gene.push_back(temp[i]);
	}
	gene.push_back((float)(rand() % 11)+1);
}
void Gene::printGene() {
	for (int i = 0; i< gene.size(); i++) {
		cout << gene.at(i) << "#";
	}
	cout << endl;
}
vector<float> Gene::getGene() {
	return this->gene;
}
void Gene::setGene(vector<float> m_gene) {
	gene = m_gene;
}
void Gene::updateGene(int pos, float value){
    gene[pos] = value;
}

