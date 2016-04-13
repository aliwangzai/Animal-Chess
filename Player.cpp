//
//  Player.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//
#include "Player.h"


Move Player::genMove(const Board& board){
    return {PointXY{0,0},PointXY{0,0}};
}


float Player::eval(const Board& board){
    //Pieces::getDistanceToEnemyBase() 获取棋子离敌方base的距离
    //pieces::getChessPower() 获取子力
    
    return 0.0f;
}
