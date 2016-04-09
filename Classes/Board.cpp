#include "Board.h"


Piece
bool Board::availableMove(Move move){
	Point ptFrom 	= move.from;
	Point ptTo 		= move .to;

	Piece pieceFrom	= getPiece(ptFrom);
	Piece pieceTo	= getPiece(ptTo);

	Type fromType	= pieceFrom.getType();
	Type toType		= pieceTo.getType(); 
	if(fromType == Piece::NIL){
		return false;
	}

	// detect jumping over the river
	bool isRiver = true;
	int diffx = ptFrom.x	- ptTo.x;
	int diffy = ptFrom.y	- ptTo.y;
	int signx = (diffx==0)?0:(diffx>0?1:-1);
	int signy = (diffy==0)?0:(diffy>0?1:-1);
	int detectX = ptFrom.x;
	int detectY = ptFrom.y;
	int i=1;
	do{
		detectX = detectX - signx * i;
		detectY = detectY - signy * i;
		if( ptTo == Point{detectX,detectY}){
			break;
		}
		isRiver &= (getTerrain(Point{detectX,detectY}) == RIVER);
		// there if there is an animal that under river
		if( isRiver && getPiece(detectX,detectY) != NIL ){
			return false;
		}
		i++;
	}while(isRiver);

	if(!isRiver){
		return false;
	}
	if(getTerrain(ptFrom) == RIVER || getTerrain(ptTo) == RIVER){
		return false;
	}
	if( !(fromType == LION || fromType == TIGER) ){
		return false;
	}

	// detect if moving into den
	if(getTerrain(ptTo) == DEN){
		if( curPlayer == 0 && ptTo.x == 3 && ptTo.y == 0){
			return false;
		}
		if(curPlayer == 1 && ptTo.x == 3 && ptTo.y == 8){
			return false;
		}
	}

	// check if the moving distance is 1
	if( abs(ptTo.x-ptFrom.x) + abs(ptTo.y-ptFrom.y) != 1 ){
		return false;
	}

	// check the river and land
	if( (getTerrain(ptTo) == RIVER && getTerrain(ptFrom) == NIL)
		|| (getTerrain(ptTo) == NIL && getTerrain(ptFrom) == RIVER) ){
		if(getPiece(ptTo).getType() != NIL ){
			return false;
		}
	}

	// check the priority of 2 piece(including the NIL)
	Piece::Type typeFrom = pieceFrom.getType();
	Piece::Type typeTo = pieceTo.getType();

	/* set the priority to lowest if it is trapped */
	if(terrain[ptTo.x][ptTo.y] == TRAP){
		typeTo = NIL;
	}

	// check mouse and elephant
	if( typeFrom == RAT && typeTo == ELEPHANT)
		return true;
	if( typeFrom == ELEPHANT && typeTo == RAT)
		return false;

	// return priority
	return (typeFrom > typeTo);
}