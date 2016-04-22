#pragma once


#include "Player.h"


#define INF 88888888.0

class AI_Min_Max : public Player{
public:
	Board *board;
	struct BestMove {
		Move move;
		float value;
	};

	virtual float eval(const Board &board) { return 0.0F; };
	Move getMove(int depth, int player);
	void CancelMove(Move& mv);
	void applyMove(Move& mv);
	AI_Min_Max(Board *board);

private:
	BestMove alphaBeta(int depth, float alpha, float beta, int player);
	void storeBestMove(vector<BestMove> &allBestMoves, BestMove best_move);
	void filterBestMoves(vector<BestMove> &allBestMoves, BestMove best_move, int player);

};