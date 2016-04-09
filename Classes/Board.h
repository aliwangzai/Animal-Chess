#pragma once


#include "Piece.h"

#include "Move.h"

class Board{

public:
	enum TypeTerrain {NIL,DEN,TRAP,RIVER};
	
	// 0,
	int curPlayer;
	Point selected;
	bool availableMove(Move move);
	void move(Move move);
	Piece getPiece(Point pt);
	TypeTerrain getTerrain(Point pt){
		return terrain[pt.x][pt.y];
	}

private:
	Piece board[9][7];
	static const Board::TypeTerrain terrain[9][7];
};

Board::TypeTerrain terrain[9][7]  = {
		{Board::NIL,Board::NIL,Board::TRAP,Board::DEN,Board::TRAP,Board::NIL,Board::NIL},
		{Board::NIL,Board::NIL,Board::NIL,Board::TRAP,Board::NIL,Board::NIL,Board::NIL},
		{Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL},
		{Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL},
		{Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL},
		{Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL},
		{Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL},
		{Board::NIL,Board::NIL,Board::NIL,Board::TRAP,Board::NIL,Board::NIL,Board::NIL},
		{Board::NIL,Board::NIL,Board::TRAP,Board::DEN,Board::TRAP,Board::NIL,Board::NIL}
};	