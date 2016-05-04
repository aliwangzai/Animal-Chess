
//
//  Gene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Gene.h"

#include <functional>
#include <algorithm>

Gene::Gene() { 
	winGames = 0; 
	drawGames = 0;
	loseGames = 0;
}

Gene::~Gene() {}

void Gene::generateRandomGene() {
	vector<float> temp;

	// River bouns
	temp.push_back((float)(rand() % 10));

	temp.push_back((float)(rand() % 11) + 1);

	for (int i = 2; i < 90; i++) {
		temp.push_back((float)(rand() % 201) + 1);
	}
	std::sort(temp.begin() + 2, temp.begin() + 10);
	for (int i = 1; i <= 8; i++) {
		std::sort(temp.begin() + i*10, temp.begin() + (i+1) * 10,greater<float>());
	}
	for (int i = 0; i < 90; i++) {
		gene.push_back(temp[i]);
	}
}
void Gene::printGene() {
	for (int i = 0; i < gene.size(); i++) {
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
void Gene::updateGene(int pos, float value) {
	gene[pos] = value;
}

