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
    virtual Move genMove(const Board &board);
    virtual float eval( const Board &board);

};
#endif /* Player_h */
