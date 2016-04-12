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
	return 0.0f;
}
