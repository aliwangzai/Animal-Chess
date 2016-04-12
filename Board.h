//
//  Board.h
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#ifndef Board_h
#define Board_h


#endif /* Board_h */

#include "Pieces.h"

#include "Move.h"

class Board{
    
public:
    enum TypeTerrain {NIL,DEN,TRAP,RIVER};
    
    // 0,
    int curPlayer;
    mPoint selected;
    bool availableMove(Move move);
    void move(Move move);
    Pieces getPiece(mPoint pt);
    TypeTerrain getTerrain(mPoint pt){
        return terrain[pt.x][pt.y];
    }
    
private:
    Pieces board[9][7];
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