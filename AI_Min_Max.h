#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
public:
	Board *board;
	Move best_move;

	virtual float eval(const Board &board) { return 0.0; };
	float alphaBeta(int depth, int alpha, int beta, int maxplayer);
	Move getMove();
	void CancelMove(Move& mv);
	void applyMove(Move& mv);

	AI_Min_Max(Board *board);
};