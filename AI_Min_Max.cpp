#include "AI_Min_Max.h"




float AI_Min_Max::AlphaBeta(int depth, int alpha, int beta){
	if (depth <= 0) {
		return Player::eval(board);
	}
	auto allMoves = genAllMoves(board);
	


	return 0.0;
}

Move AI_Min_Max::getMove()
{
	return Move();
}

AI_Min_Max::AI_Min_Max(const Board & board)
{
	this->board = board;
}
