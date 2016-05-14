#include "AI_Min_Max.h"

#include "time.h"
#include <algorithm>
#include <assert.h>


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
                //return BestMove{ Move(),alpha };
                break;
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
            if (beta < alpha)
                //return BestMove{ Move(),beta };
                break;
        }
    }
    
    std::sort(allBestMoves.begin(), allBestMoves.end(), [](const BestMove &a, const BestMove &b)->bool{
        return a.value > b.value;
    });
    
    if (abs(best_move.value) > 5000) {
        return best_move;
    }
    else {
        auto sizeCandidates = allBestMoves.size();
        assert(sizeCandidates != 0);
        auto _rand = 1.0 * rand() / INT_MAX;
        if (_rand > 0.95)
            return allBestMoves[0 % sizeCandidates];
        if (_rand > 0.04)
            return allBestMoves[1 % sizeCandidates];
        else
            return allBestMoves[2 % sizeCandidates];
    }
    
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
	Player::cancelMove(mv, board);
}

AI_Min_Max::AI_Min_Max(Board *board)
{
    this->board = board;
}