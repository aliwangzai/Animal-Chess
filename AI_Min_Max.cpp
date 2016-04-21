#include "AI_Min_Max.h"
#include "time.h"


AI_Min_Max::BestMove AI_Min_Max::alphaBeta(int depth, int alpha, int beta, int player){
	BestMove best_move{ Move(),0.0 };
	vector<BestMove> allBestMoves;

	if (depth <= 0 ) {
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
			if (val.value >= best_move.value) {
				best_move = val;
				if (allBestMoves.size() < 5)
					allBestMoves.push_back(best_move);
				else
					allBestMoves[rand() % 5] = best_move;
			}
			if (best_move.value > alpha)
				alpha = best_move.value;
			if(beta < alpha){
				BestMove ret{ Move(),alpha };
				return ret;
			}
		}
		filterBestMoves(allBestMoves, best_move, 1);
	}else{
		best_move.value = INT_MAX;
		for( auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta( depth-1, alpha, beta, true );
			val.move = mv;
			CancelMove(mv);
			if (val.value <= best_move.value) {
				best_move = val;
				if (allBestMoves.size() < 5)
					allBestMoves.push_back(best_move);
				else
					allBestMoves[rand() % 5] = best_move;
			}
			if (best_move.value < beta )
				beta = best_move.value;
			if( beta < alpha ){
				BestMove ret{ Move(),beta };
				return ret;
			}
		}
		filterBestMoves(allBestMoves,best_move,0);
	}
	return allBestMoves[rand() % allBestMoves.size()];
}

Move AI_Min_Max::getMove(int depth, int player)
{
	
	auto best_move = alphaBeta(depth, INT_MIN, INT_MAX, 1);
	return best_move.move;
}

void AI_Min_Max::applyMove(Move & mv)
{
	board->moveChess(mv, false);
	//board->fcoutBoard();
}

void AI_Min_Max::filterBestMoves(vector<BestMove>& allBestMoves, BestMove best_move, int player)
{
	for (auto it = allBestMoves.begin(); it < allBestMoves.end();) {
		if (player)
			if (it->value < best_move.value)
				it = allBestMoves.erase(it);
			else
				it++;
		else
			if (it->value > best_move.value)
				it = allBestMoves.erase(it);
			else
				it++;
	}
	
}

void AI_Min_Max::CancelMove(Move& mv)
{
	auto from = mv.from;
	auto to = mv.to;
	auto toPiece = board->getPiece(to);
	board->boardPieces[from.x][from.y] = board->boardPieces[to.x][to.y];
	toPiece->setPositionBlock(from, false);
	if (mv.eatenIndex != -1) {
		auto eatenPiece = board->allPieces[mv.eatenIndex];
		board->boardPieces[to.x][to.y] = eatenPiece;
		eatenPiece->setPositionBlock(to, false);
		eatenPiece->setEatenValue(false);
		board->nPiecesExisted[eatenPiece->getPlayer()] ++;
	} else {
		board->boardPieces[to.x][to.y] = board->nul_piece;
	}
	board->currentPlayer = !board->currentPlayer;
	//board->fcoutBoard();
}

AI_Min_Max::AI_Min_Max(Board *board)
{
	this->board = board;
}
