#include "AI_Min_Max.h"



float AI_Min_Max::alphaBeta(int depth, int alpha, int beta, int maxplayer){
	if (depth <= 0) {
		return Player::eval(*board);
	}
	auto allMoves = genAllMoves(*board);

	if(maxplayer){
		float best_value = INT_MIN;
		for(auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta(depth-1, alpha, beta, false);
			CancelMove(mv);
			alpha = alpha > best_value ? alpha : best_value;
			if(beta <= alpha){
				return alpha;
			}
			if(best_value < val){
				best_value = val;
				best_move = mv;
			}
		}
		return best_value;
	}else{
		float best_value = INT_MAX;
		for( auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta( depth-1, alpha, beta, true );
			CancelMove(mv);
			beta = beta < val ? beta : val;
			if( beta <= alpha ){
				return beta;
			}
			if(best_value > val ){
				best_value = val;
				best_move = mv;
			}
		}
		return best_value;
	}
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
