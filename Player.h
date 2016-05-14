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
#include <vector>
#include "Move.h"
#include "Pieces.h"
#include "Board.h"

#define INF 88888888.0

using namespace std;
class Player{
public:
    string name;
	int player;
    virtual vector<Move> genAllMoves( Board &board);
    float eval( Board &board);
    vector<Move> genAMove( Board &board, Pieces * fromPiece);
	virtual void cancelMove(Move &mv, Board *board);
    
	Player();
	~Player();
private:
	bool TLBesideRiver(Board &board, Pieces *piece);
};
#endif /* Player_h */
