#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
public:
	Move genMove(const Board &board);
	float eval( const Board &board);

	Board board;

	AI_Min_Max(const Board& board){
		this->board = board;
	}
};