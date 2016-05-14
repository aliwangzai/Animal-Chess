#include "MCTS_Tree_Node.h"

MCTS_Tree_Node::MCTS_Tree_Node(Board *_board)
{
	this->board = new Board();
	this->board->copy_from_JustData(_board);
	depth = 0;
	visited_times = 0;
	total_value = 0.0;
	root = NULL;
	fromMove = Move();
	how_many_diff_children_are_visited = 0;
	bounds[0] = INF;
	bounds[1] = -INF;
}

MCTS_Tree_Node::~MCTS_Tree_Node()
{
	if (board)
		delete board;
	board = nullptr;
	for (int i = 0; i < children.size(); i++) {
		if (children[i]) {
			has_children_visited[children[i]] = false;
			delete children[i];
			children[i] = NULL;
		}
	}
}

void MCTS_Tree_Node::genChildren()
{
	if (children.size() == 0) {
		auto allMoves = Player::genAllMoves(*board);
		for (auto mv : allMoves) {
			MCTS_Tree_Node *tmp = new MCTS_Tree_Node(board);
			tmp->fromMove = mv;
			tmp->root = this;
			tmp->depth = this->depth + 1;
			tmp->board->moveChess(mv, false);
			children.push_back(tmp);
		}
	}
}

bool MCTS_Tree_Node::fullyExpanded()
{
	return (how_many_diff_children_are_visited == children.size());
}
