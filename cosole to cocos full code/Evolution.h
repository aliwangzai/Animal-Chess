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
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Evolution {
private:
	
	float crossCoverRate;
	float mutationRate;
	Evolution();
	static Evolution* m_pInstance;
public:
    int p1;
    int p2;
    //int loseGames;
    int generationNum;
    bool evolutionEnd;
    vector<Gene> population;
	static Evolution* GetInstance() {
		if (m_pInstance == NULL)  //判断是否第一次调用
			m_pInstance = new Evolution();
		return m_pInstance;
	}
	~Evolution();
	void generatePopulation(int popuNum);
	void mutation(int genePos);
	void crossCover(int genePos1, int genePos2);
	void select();
	int getGenerationNum();
	void storePopulationGenes();
	void loadPopulationGenes();
};

#endif /* Evolution_h */