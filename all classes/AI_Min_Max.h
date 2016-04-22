#pragma once


#include "Player.h"
#define INF 88888888

class AI_Min_Max : public Player{
public:
	Board *board;
	struct BestMove {
		Move move;
		float value;
	};

	virtual float eval(const Board &board) { return 0.0; };
	Move getMove(int depth, int player);
	void CancelMove(Move& mv);
	void applyMove(Move& mv);
	void filterBestMoves(vector<BestMove> &allBestMoves, BestMove best_move, int player);
	AI_Min_Max(Board *board);

private:
	BestMove alphaBeta(int depth, int alpha, int beta, int player);
	int alphaBeta2(int depth, int alpha, int beta, Move &move);
	void storeBestMove(vector<BestMove> &allBestMoves, BestMove best_move);
};