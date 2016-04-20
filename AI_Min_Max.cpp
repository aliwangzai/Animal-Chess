#include "AI_Min_Max.h"



AI_Min_Max::BestMove AI_Min_Max::alphaBeta(int depth, int alpha, int beta, int player){
	BestMove best_move{ Move(),0.0 };
	if (depth <= 0) {
		best_move.value = Player::eval(*board);
		return best_move;
	}
	auto allMoves = genAllMoves(*board);

	if(player){
		best_move.value = INT_MIN;
		for(auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta(depth-1, alpha, beta, false);
			val.move = mv;
			CancelMove(mv);
			if (val.value > alpha) alpha = val.value;
			if(beta <= alpha){
				BestMove ret{ Move(),alpha };
				return ret;
			}
			if (best_move.value < val.value) {
				best_move = val;
			}
		}
	}else{
		best_move.value = INT_MAX;
		for( auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta( depth-1, alpha, beta, true );
			val.move = mv;
			CancelMove(mv);
			
			if (val.value < beta ) beta = val.value;
			if( beta <= alpha ){
				BestMove ret{ Move(),beta };
				return ret;
			}
			if (val.value < best_move.value) {
				best_move = val;
			}
		}
	}
	return best_move;
}

Move AI_Min_Max::getMove(int depth, int player)
{
	auto best_move = alphaBeta(2, INT_MIN, INT_MAX, 1);
	return best_move.move;
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
		eatenPiece->setPositionBlock(to, false);
		eatenPiece->setEatenValue(false);
		board->nPiecesExisted[eatenPiece->getPlayer()] ++;
	} else {
		board->boardPieces[to.x][to.y] = board->nul_piece;
	}
	board->currentPlayer = !board->currentPlayer;
}

AI_Min_Max::AI_Min_Max(Board *board)
{
	this->board = board;
}
