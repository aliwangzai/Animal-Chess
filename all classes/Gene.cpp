//
//  Gene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Gene.h"

Gene::Gene(){ winState = 0;}
Gene::~Gene(){}

void Gene::generateRandomGene(){
    for(int i = 0; i<21;i++){
        gene.push_back((float)rand()/RAND_MAX);
    }
}
void Gene::printGene(){
    for(int i = 0; i< gene.size();i++){
        cout<<gene.at(i)<<"#";
    }
    cout<<endl;
}
vector<float> Gene::getGene(){
    return this->gene;
}

