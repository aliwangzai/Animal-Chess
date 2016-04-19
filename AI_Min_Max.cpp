#include "AI_Min_Max.h"




float AI_Min_Max::alphaBeta(int depth, int alpha, int beta){
	if (depth <= 0) {
		return Player::eval(*board);
	}
	auto allMoves = genAllMoves(*board);
	
	for (auto mv : allMoves) {
		applyMove(mv);
		auto val = -alphaBeta(depth - 1, -beta, -alpha);
		if(val >= beta)
			return beta;
		if (val > alpha)
			alpha = val;
		best_move = mv;
		CancelMove(mv);
	}
	return alpha;
}

Move AI_Min_Max::getMove()
{
	return Move();
}

void AI_Min_Max::applyMove(Move & mv)
{
	board->moveChess(mv, false);
}

void AI_Min_Max::CancelMove(Move& mv)
{
	auto from = mv.from;
	auto to = mv.to;
	auto toPiece = board->getPiece(to);
	auto eatInfo = mv.eatinfo;
	board->boardPieces[from.x][from.y] = board->boardPieces[to.x][to.y];
	toPiece->setPositionBlock(from, false);
	if (eatInfo) {
		auto eatenPiece = board->allPieces[eatInfo->indexInAllPieces];
		board->boardPieces[to.x][to.y] = eatenPiece;
		eatenPiece->setPositionBlock(to,false);
	} else {
		board->boardPieces[to.x][to.y] = board->nul_piece;
	}
	board->currentPlayer = !board->currentPlayer;
}

AI_Min_Max::AI_Min_Max(Board *board)
{
	this->board = board;
}
