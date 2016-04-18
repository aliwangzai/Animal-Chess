//
//  Board.h
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#ifndef Board_h
#define Board_h




#include "Pieces.h"
#include <vector>
#include "Move.h"
//#include "GameScene.h"


using namespace std;

class Board {

public:
	enum TypeTerrain { NIL, DEN0, DEN1, TRAP, RIVER };

	//0,1
	int currentPlayer;
	Pieces* selected;
	bool availableMove(Move move);
	Pieces* getPiece(PointXY pt);
	inline TypeTerrain getTerrain(PointXY pt) {
		return terrain[pt.x][pt.y];
	}

	void initPieces(TMXTiledMap* map);
	void moveChess(Move move);
	// -1 if no winner, else return player
	int getWinner();

	vector<Pieces*> allPieces;
	vector<vector<Pieces*>> boardPieces;
	Pieces* nul_piece;
    
	inline bool hasPiece(Pieces::TypePiece Type, int player);
    bool hasElephant1,hasElephant2;
    
	Board();
	~Board();
private:
	vector<vector<Board::TypeTerrain>> terrain;
    
};
#endif /* Board_h */


