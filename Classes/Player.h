#pragma once

#include <string>
#include "Move.h"
#include "Piece.h"
#include "Board.h"

#include <vector>

using namespace std;

class Player{
public:
	string name;
	virtual Move genMove(const Board &board){};
	vector<Move> possible_move;
	vector<Piece> available_piece;
};