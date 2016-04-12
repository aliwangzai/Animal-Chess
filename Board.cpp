//
//  Board.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#include "Board.h"
#include "cocos2d.h"

using namespace cocos2d;

bool Board::availableMove(Move move){
    mPoint ptFrom 	    = move.from;
    mPoint ptTo 		= move.to;
    
    Pieces pieceFrom	= getPiece(ptFrom);
    Pieces pieceTo	    = getPiece(ptTo);
    
    Pieces::TypePiece fromType	= pieceFrom.getType();
    Pieces::TypePiece toType	= pieceTo.getType();
    if(fromType == Pieces::NIL){
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
        if( ptTo.x == detectX && ptTo.y == detectY){
            break;
        }
        mPoint myp;
        myp.x = detectX;
        myp.y = detectY;
        isRiver &= (getTerrain(myp) == RIVER);
        // there if there is an animal that under river
        if( isRiver && getPiece(myp).getType() != Board::NIL ){
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
    if( !(fromType == Pieces::LION || fromType == Pieces::TIGER) ){
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
    Pieces::TypePiece typeFrom = pieceFrom.getType();
    Pieces::TypePiece typeTo = pieceTo.getType();
    
    // set the priority to lowest if it is trapped
    if(terrain[ptTo.x][ptTo.y] == Board::TRAP){
        typeTo = Board::NIL;
    }
    
    // check mouse and elephant
    if( typeFrom == Pieces::RAT && typeTo == Pieces::ELEPHANT)
        return true;
    if( typeFrom == Pieces::ELEPHANT && typeTo == Pieces::RAT)
        return false;
    
    // return priority
    return (typeFrom > typeTo);
}

*/