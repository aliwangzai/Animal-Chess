#include "AI_Min_Max.h"
#include "time.h"
#include <algorithm>



AI_Min_Max::BestMove AI_Min_Max::alphaBeta(int depth, float alpha, float beta, int player) {
	vector<BestMove> allBestMoves;
	BestMove best_move{ Move(),-INF };

	if (depth <= 0 || board->getWinner() != -1) {
		best_move.value = Player::eval(*board);
		return best_move;
	}

	auto allMoves = genAllMoves(*board);
	BestMove val;
	std::sort(allMoves.begin(), allMoves.end(), [](const Move &a, const Move &b)->bool{
		return a.eatenIndex > b.eatenIndex;
	});

	if (player) {
		best_move.value = -INF;
		for (auto mv : allMoves) {
			applyMove(mv);
			if(mv.eatenIndex < 2) // no piece eaten
				val = alphaBeta(depth -1, alpha, beta, !player);
			else
				val = alphaBeta(depth - 1, alpha, beta, !player);
			val.move = mv;
			CancelMove(mv);
			if (val.value > best_move.value) {
				best_move = val;
				filterBestMoves(allBestMoves, best_move, player);
				storeBestMove(allBestMoves, best_move);
			}
			if (val.value >= alpha)
				alpha = val.value;
			if (beta < alpha)
				return BestMove{ Move(),alpha };
		}
	} else {
		best_move.value = INF;
		for (auto mv : allMoves) {
			applyMove(mv);
			if (mv.eatenIndex < 2) // no piece eaten
				val = alphaBeta(depth - 1, alpha, beta, !player );
			else
				val = alphaBeta(depth -1, alpha, beta, !player);
			val.move = mv;
			CancelMove(mv);
			if (val.value < best_move.value) {
				best_move = val;
				filterBestMoves(allBestMoves, best_move,player);
				storeBestMove(allBestMoves, best_move);
			}
			if (val.value < beta)
				beta = val.value;
			if (beta <= alpha)
				return BestMove{ Move(),beta };
		}
	}
    
    std::sort(allBestMoves.begin(), allBestMoves.end(), [](const BestMove &a, const BestMove &b)->bool{
        return a.value > b.value;
    });
    auto sizeCandidates = allBestMoves.size();
    if(1.0*rand() / INT_MAX > 0.70)
        return allBestMoves[0 % sizeCandidates];
    if(1.0*rand() / INT_MAX > 0.20)
        return allBestMoves[1 % sizeCandidates];
    else
        return allBestMoves[2 % sizeCandidates];

	return best_move;

}

void AI_Min_Max::storeBestMove(vector<BestMove>& allBestMoves, BestMove best_move)
{
	if (allBestMoves.size() < 3)
		allBestMoves.push_back(best_move);
	else
		allBestMoves[rand() % 3] = best_move;
}

Move AI_Min_Max::getMove(int depth, int player)
{
	auto best_move = alphaBeta(depth, INT_MIN, INT_MAX, player);
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
			if ( it->value < best_move.value )
				it = allBestMoves.erase(it);
			else
				it++;
		else
			if (it->value > best_move.value )
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