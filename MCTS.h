#pragma once

#include "Move.h"
#include "Board.h"
#include "Player.h"
#include "MCTS_Tree_Node.h"
#include "MyTimer.h"


class MCTS : public MCTS_Tree_Node{
public:
	MCTS(Board *_board);
	~MCTS();

public:
	Move MCTS_Search(MyTimer &timer, int _player);
private:
	//from Player class
	void applyMove(Move &mv);
	void cancelMove(Move &mv);

	MCTS_Tree_Node* treePolicy(MyTimer &timer);

	MCTS_Tree_Node* expand(MCTS_Tree_Node *node);

	MCTS_Tree_Node* bestChild(MCTS_Tree_Node *node);

	double rollOut(MCTS_Tree_Node *node);

	bool isGameEnd(Board *board, int depth);

	double normalise(double x, double a, double b);

	void backup(MCTS_Tree_Node* node, double val);

	bool equalBoard(Board *a, Board *b);

//members
public:
	Board *board;

};
