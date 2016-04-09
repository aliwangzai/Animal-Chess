#include "piece.h"


Piece::Type Piece::getType(){
	return type;
}


Point Piece::getPosition(){
	return Pos;
}

int Piece::getPlayer(){
	return player;
}