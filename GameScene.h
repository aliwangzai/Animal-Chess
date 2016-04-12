//
//  GameScene.h
//  Animal
//
//  Created by yang_xiong on 16/4/7.
//
//

#ifndef GameScene_h
#define GameScene_h
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Pieces.h"

USING_NS_CC;

class GameScene :public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void initPieces(TMXTiledMap* map);
    Vector<Pieces*> BoardPiece;
    void moveChess(Pieces* fromPiece, Point to, Pieces* toPiece = nullptr);
    bool moveable(Point from,Point to);
    
    Pieces* pieceSelected;
    int currentPlayer;
    int clickNum;
    int fromIndex,toIndex;
};

#endif /* GameScene_h */
