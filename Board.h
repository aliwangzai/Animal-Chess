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
#include <vector>
#include "Move.h"


using namespace std;

class Board{
    
public:
    enum TypeTerrain {NIL,DEN,TRAP,RIVER};
    
    // 0,
    int curPlayer;
    int selected_index;
    bool availableMove(Move move);
    void move(Move move);
    int getPiece(Point pt);
    TypeTerrain getTerrain(Point pt){
        return terrain[(int)pt.x][(int)pt.y];
    }

	void initPieces(TMXTiledMap* map);
	vector<Pieces*> BoardPiece;
	void moveChess(Pieces* fromPiece, Point to, Pieces* toPiece = nullptr);
	bool moveable(Point from, Point to);

	int currentPlayer;
    
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