#include "Piece.h"


Piece::TypePiece Piece::getType(){
	return type;
}


Point Piece::getPosition(){
	return Pos;
}

int Piece::getPlayer(){
	return Player;
}