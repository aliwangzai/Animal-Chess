#include "AI_Min_Max.h"




float AI_Min_Max::AlphaBeta(int depth, int alpha, int beta){
	if (depth <= 0) {
		return Player::eval(board);
	}

	return 0.0;
}

AI_Min_Max::AI_Min_Max(const Board & board)
{
	this->board = board;
}
