#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
public:
	//vector<Move> genMove(const Board &board);
	virtual float eval(const Board &board) { return 0.0; };
	float AlphaBeta(int depth, int alpha, int beta);
	Board board;

	AI_Min_Max(const Board& board);
};