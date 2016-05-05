#ifndef Board_h
#define Board_h




#include "Pieces.h"
#include <vector>
#include "Move.h"
//#include "GameScene.h"


using namespace std;

class Board {
    
public:
    enum TypeTerrain { NIL, DEN0, DEN1, TRAP, RIVER, OUT_OF_BOUNDARY };
    
    //0,1
    int currentPlayer;
    //0,1
    int whoWillMove;
    
    bool isThinking;
    Pieces* selected;
    Pieces* nul_piece;
    vector<Pieces*> allPieces;
    vector<vector<Pieces*> > boardPieces;
    vector<Move> moveHistory;
    int nPiecesExisted[2];
    
    
    Pieces* getPiece(PointXY pt);
    Pieces* getPiece(Pieces::TypePiece type, int player);
    bool availableMove(Move move);
    inline TypeTerrain getTerrain(PointXY pt) {
        if (pt.x < 0 || pt.y < 0 || pt.x > 8 || pt.y > 6)
            return OUT_OF_BOUNDARY;
        return terrain[pt.x][pt.y];
    }
    
    
    
    int getPieceIndex(Pieces::TypePiece type, int player);
    
    void initPieces(TMXTiledMap* map);
    void moveChess(Move &move, bool realMove = true);
    
    
    // -1 if no winner, else return player
    int getWinner();
    
    
    bool hasPiece(Pieces::TypePiece type, int player);
    void fcoutBoard();
    
    
    void releaseMem();
    Board();
    ~Board();
private:
    vector<vector<Board::TypeTerrain> > terrain;
    
};
#endif /* Board_h */
