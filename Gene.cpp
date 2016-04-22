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
    for(int i = 0; i<20;i++){
        gene.push_back((float)(rand()%101));
    }
    gene.push_back((float)(rand()%11));
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
void Gene::setGene(vector<float> m_gene){
    gene = m_gene;
}

