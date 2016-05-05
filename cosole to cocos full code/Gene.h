//
//  Gene.h
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#ifndef Gene_h
#define Gene_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Move.h"
using namespace std;
/*
 [0] : river bouns
 [1] : threaten ratio
 [2] ~ [9] : piece power
 [10] ~ [19] : Rat's dis
 [20] ~ [29] : Cat's dis
 ...
 [type * 10] ~ [type * 10 + 9] : type's dis
 */
class Gene {
private:
    vector<float> gene;
public:
    int winGames;
    int loseGames;
    int drawGames;
    
    Gene();
    ~Gene();
    void generateRandomGene();
    void printGene();
    vector<float>getGene();
    void setGene(vector<float> m_gene);
    void updateGene(int pos, float value);
};

#endif /* Gene_h */