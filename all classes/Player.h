//
//  Player.h
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#ifndef Player_h
#define Player_h
#include <string>
#include "Move.h"
#include "Pieces.h"
#include "Board.h"

#include <vector>

using namespace std;

class Player{
public:
    string name;
    virtual vector<Move> genAllMoves( Board &board);
    virtual int eval( Board &board);
    vector<Move> genAMove( Board &board, Pieces * fromPiece);
    
};
#endif /* Player_h */
