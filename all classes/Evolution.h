//
//  Evolution.h
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#ifndef Evolution_h
#define Evolution_h
#include "Gene.h"
#include <vector>
using namespace std;
class Evolution{
private:
    vector<Gene> population;
    int generationNum;
    float crossCoverRate;
    float mutationRate;
public:
    Evolution(int g_Num,int P_Num);//generation num and population num;
    ~Evolution();
    void generatePopulation(int popuNum);
    void mutation(int genePos, float mutationRate);
    void crossCover(int genePos1,int genePos2,float crossCoverRate);
    void select();
    int getGenerationNum();
    void storePopulationGenes();
    void loadPopulationGenes();
};

#endif /* Evolution_h */
