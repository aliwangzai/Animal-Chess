#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
public:
	Board board;

	virtual float eval(const Board &board) { return 0.0; };
	float AlphaBeta(int depth, int alpha, int beta);
	Move getMove();
	void CancelMove(Move mv);


	AI_Min_Max(const Board& board);
};