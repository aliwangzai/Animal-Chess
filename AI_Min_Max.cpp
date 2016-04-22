#include "AI_Min_Max.h"
#include "time.h"




AI_Min_Max::BestMove AI_Min_Max::alphaBeta(int depth, int alpha, int beta, int player){
	BestMove best_move{ Move(),-INF };
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
			auto val = alphaBeta(depth-1, alpha, beta, !player);
			val.move = mv;
			CancelMove(mv);
			if (val.value >= best_move.value) {
				best_move = val;
				alpha = val.value;
				storeBestMove(allBestMoves, best_move);
			}
			if (beta < alpha )
				return BestMove { Move(),alpha };
		}
		filterBestMoves(allBestMoves, best_move, 1);
	}else{
		best_move.value = INT_MAX;
		for( auto mv : allMoves ){
			applyMove(mv);
			auto val = alphaBeta( depth-1, alpha, beta, !player);
			val.move = mv;
			CancelMove(mv);
			if (val.value <= best_move.value) {
				best_move = val;
				beta = val.value;
				storeBestMove(allBestMoves, best_move);
			}
			if( val.value < alpha )
				return BestMove{ Move(),beta };
		}
		filterBestMoves(allBestMoves,best_move,0);
	}
	

	return allBestMoves[rand() % allBestMoves.size()];
	
}

void AI_Min_Max::storeBestMove(vector<BestMove>& allBestMoves, BestMove best_move)
{
	if (allBestMoves.size() < 5)
		allBestMoves.push_back(best_move);
	else
		allBestMoves[rand() % 5] = best_move;
}


int AI_Min_Max::alphaBeta2(int depth, int alpha, int beta, BestMove &move)
{
	vector<BestMove> allBestMoves;
	BestMove best_move;

	if (depth <= 0)
		return Player::eval(*board);
	// Null move
	//board->currentPlayer = !board->currentPlayer;
	//auto val = -alphaBeta2(depth - 3, -beta, -beta + 1, BestMove());
	//board->currentPlayer = !board->currentPlayer;
	//if (val >= beta)
		//return beta;
	// End of null move

	auto allMoves = genAllMoves(*board);
	for (auto mv : allMoves) {
		applyMove(mv);
		int val = -alphaBeta2(depth - 1, -beta, -alpha, best_move);
		CancelMove(mv);
		if (val >= beta)
			return beta;
		if (val > alpha) {
			alpha = val;
			move.move = mv;	move.value = val;
		}
	}
	return alpha;
}

Move AI_Min_Max::getMove(int depth, int player)
{
	
	//auto best_move = alphaBeta(depth, INT_MIN, INT_MAX, player);
	BestMove best_move;
	alphaBeta2(depth, -INF, INF, best_move);
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
