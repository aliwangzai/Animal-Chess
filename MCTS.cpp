#include "MCTS.h"


MCTS::MCTS(Board * _board) : MCTS_Tree_Node(_board)
{
	this->board = _board;
}

MCTS::~MCTS()
{
}

Move MCTS::MCTS_Search(MyTimer &timer, int _player)
{
	Player::player = _player;
	genChildren();

	while (timer.hasTime()) {
		assert(children.size() != 0);
		auto tree_policy_node = treePolicy(timer);
		auto delta = rollOut(tree_policy_node);
		backup(tree_policy_node, delta);
	}
	//board->foutBoard();
	auto ret = bestChild(this)->fromMove;
	return ret;
}

void MCTS::applyMove(Move &mv)
{
	board->moveChess(mv, false);
	//board->foutBoard();
}

void MCTS::cancelMove(Move & mv)
{
	Player::cancelMove(mv, board);
	//board->foutBoard();
}

MCTS_Tree_Node* MCTS::treePolicy(MyTimer &timer )
{
	MCTS_Tree_Node *cur = this;
	while (timer.hasTime() && !isGameEnd(cur->board,cur->depth)) {
		cur->genChildren();
		if (!cur->fullyExpanded()) {
			auto ret = expand(cur);
			return ret;
		} else {
			auto cur2 = cur;
			cur = bestChild(cur);
			cur->genChildren();
		}
	}
	return cur;
}

MCTS_Tree_Node* MCTS::expand(MCTS_Tree_Node *node)
{
	node->genChildren();
	for (auto child : node->children) {
		if (node->has_children_visited[child] == false) {
			//visite and return
			node->has_children_visited[child] = true;
			node->how_many_diff_children_are_visited++;
			return child;
		}
	}
	assert(1);
	return NULL;
}

MCTS_Tree_Node * MCTS::bestChild(MCTS_Tree_Node * node)
{
	double best_value = board->currentPlayer == 0?FLT_MAX:-FLT_MAX;
	MCTS_Tree_Node *ret = NULL;
	for (auto child : node->children) {
		double uctValue_1st_Term = child->total_value / (child->visited_times + 1);
		uctValue_1st_Term = normalise(uctValue_1st_Term, bounds[0], bounds[1]);

		double uctValue = uctValue_1st_Term + c * sqrt(2 * log(this->visited_times + 1) / (child->visited_times + 1));
		
		if (board->currentPlayer == 0) {
			if (uctValue < best_value) {
				ret = child;
				best_value = uctValue;
			}
		} else {
			if (uctValue > best_value) {
				ret = child;
				best_value = uctValue;
			}
		}
	}
	return ret;
}

double MCTS::rollOut(MCTS_Tree_Node *node)
{
	MCTS_Tree_Node* ret = NULL;

	Board simulation_board;
	simulation_board.copy_from_JustData(node->board);
	int depth = node->depth;

	//node->board->foutBoard();
	// randomly play this game until game ends
	while (!isGameEnd( &simulation_board, depth )) {
		auto allMoves = Player::genAllMoves(simulation_board);
		if (allMoves.size() != 0) {
			simulation_board.moveChess(allMoves[rand() % allMoves.size()], false);
			depth++;
		} else {
			break;
		}
	}

	//simulation_board.foutBoard();

	double delta = eval(simulation_board);
	if (delta < node->bounds[0])
		node->bounds[0] = delta;
	if (delta > node->bounds[1])
		node->bounds[1] = delta;
	return delta;
}

bool MCTS::isGameEnd(Board * _board, int depth)
{
	if (depth >= MAXIMUM_DEPTH)
		return true;
	if (_board->getWinner() != -1)
		return true;
	return false;
}

double MCTS::normalise(double x, double a, double b)
{
	if (a >= b)
		return x;
	else
		return (x - a) / (b - a);
}

void MCTS::backup(MCTS_Tree_Node * node, double val)
{
	auto cur = node;
	while (cur) {
		cur->visited_times++;
		cur->total_value += val;
		cur = cur->root;
	}
}

bool MCTS::equalBoard(Board * a, Board * b)
{
	bool ret = true;
	ret &= a->currentPlayer == b->currentPlayer;
	ret &= a->moveHistory.size() == b->moveHistory.size();
	if (!ret) 
		return ret;
	for (auto i = 0; i < a->moveHistory.size(); i++) 
		ret &= a->moveHistory[i] == b->moveHistory[i];
	
	ret &= a->nPiecesExisted[0] == b->nPiecesExisted[0];
	ret &= a->nPiecesExisted[1] == b->nPiecesExisted[1];
	if (!ret)
		return ret;
	for (int x = 0; x < 9; x++) 
		for (int y = 0; y < 6; y++) {
			ret &= a->boardPieces[x][y]->getType() == b->boardPieces[x][y]->getType();
			ret &= a->boardPieces[x][y]->isEaten() == b->boardPieces[x][y]->isEaten();
		}
	return ret;
}
