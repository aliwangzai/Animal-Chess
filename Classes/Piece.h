#pragma once


#include "Move.h"

class Piece{
public:
	enum TypePiece {NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT};
private:
	Point Pos;
	int Player;
	TypePiece type;

public:
	TypePiece getType();
	Point getPosition();
	int getPlayer();
};


