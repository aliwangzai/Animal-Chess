
//
//  Gene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Gene.h"
#include <algorithm>

Gene::Gene() { winState = 0; }
Gene::~Gene() {}

void Gene::generateRandomGene() {
    vector<float> temp;
    for(int i  = 0 ; i<18;i++){
        temp.push_back((float)(rand() % 201)+1);
    }

	// [0] ~ [7] : piece power
	// [8] ~ [17] : [distance+6] value, distance==0 and 1 are defined in pieces.cpp
    std::sort(temp.begin(),temp.begin()+8);
    std::sort(temp.begin()+8,temp.end());
    std::reverse(temp.begin()+8, temp.end());
	for (int i = 0; i<18; i++) {
        gene.push_back(temp[i]);
	}
	
	// [18] : Threaten ratio
	gene.push_back((float)(rand() % 11)+1);
    
    // [19] : River bouns
    gene.push_back((float)(rand() % 10));
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

