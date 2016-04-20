#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
public:
	Board *board;
	struct BestMove {
		Move move;
		float value;
	};

	virtual float eval(const Board &board) { return 0.0; };
	BestMove alphaBeta(int depth, int alpha, int beta, int player);
	Move getMove(int depth, int player);
	void CancelMove(Move& mv);
	void applyMove(Move& mv);

	AI_Min_Max(Board *board);
};