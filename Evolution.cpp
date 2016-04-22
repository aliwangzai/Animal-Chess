//
//  Evolution.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#include "Evolution.h"

Evolution::Evolution(int g_Num,int P_Num){//generation num and population num;
    crossCoverRate = 0.3;
    mutationRate = 0.05;
    generationNum = g_Num;
    generatePopulation(P_Num);
}
Evolution::~Evolution(){}
void Evolution::generatePopulation(int popuNum){
    for(int i = 0; i < popuNum ;i++){
        Gene newgene = Gene::Gene();
        newgene.generateRandomGene();
        population.push_back(newgene);
    }
    
}
void Evolution::mutation(int genePos, float mutationRate){
    for(int i = 0;i<21;i++){
        float a = (float)rand()/RAND_MAX;
        if(a<mutationRate)
           population.at(genePos).getGene().at(i) = (float)rand()/RAND_MAX;
    }
}
void Evolution::crossCover(int genePos1,int genePos2,float crossCoverRate){
    for(int i = 0 ;i<21;i++){
        float a = (float)rand()/RAND_MAX;
        if(a<crossCoverRate){
            float temp = population.at(genePos1).getGene().at(i);
            population.at(genePos1).getGene().at(i) = population.at(genePos2).getGene().at(i);
            population.at(genePos2).getGene().at(i) = temp;
        }
    }
}
void Evolution::select(){
    if(generationNum>0){
        vector<Gene> temp;
        
        for(int i = 0 ;i<population.size();i++){ //get the winner gene
            if(population.at(i).winState == 1){
                temp.push_back(population.at(i));
            }
        }
        population = temp;
        
        for(int j = 0; j< population.size()/2;j++){//do crosscover
            crossCover(j, population.size()-1-j, crossCoverRate);
        }
        
        for(int k = 0; k<population.size();k++){  //do mutation
            mutation(k,mutationRate);
        }
        
        for(int l = 0; l< temp.size();l++){ //add unchanged gene to population
            population.push_back(temp.at(l));
        }
        
        generationNum--;
    }
}

int Evolution::getGenerationNum(){
    return generationNum;
}
void Evolution::storePopulationGenes(){
    
}
void Evolution::loadPopulationGenes(){
    
}