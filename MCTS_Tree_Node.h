#pragma once
#include "Board.h"
#include "Player.h"

class MCTS_Tree_Node : public Player{
public:
	MCTS_Tree_Node( Board *_board);
	~MCTS_Tree_Node();
public:
	const double c = 4.0f;
	const int MAXIMUM_DEPTH = 100;

	double bounds[2];
	Board *board;
	MCTS_Tree_Node *root;
	vector<MCTS_Tree_Node*> children;
	int depth;
	int visited_times;
	double total_value;
	Move fromMove;
	unordered_map<MCTS_Tree_Node*,bool> has_children_visited;
	int how_many_diff_children_are_visited;
public:
	void genChildren();
	bool fullyExpanded();


};
