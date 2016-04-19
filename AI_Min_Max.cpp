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

void AI_Min_Max::CancelMove(Move mv)
{
	auto from = mv.from;
	auto to = mv.to;
	auto eatInfo = mv.eatinfo;
	board.boardPieces[from.x][from.y] = board.boardPieces[to.x][to.y];
	if (eatInfo) {
		auto eatenPiece = board.allPieces[eatInfo->indexInAllPieces];
		board.boardPieces[to.x][to.y] = eatenPiece;
		eatenPiece->setPositionBlock(to);
	}

}

AI_Min_Max::AI_Min_Max(const Board & board)
{
	this->board = board;
}
