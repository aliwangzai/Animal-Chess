//
//  GameScene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/7.
//
//

#include "GameScene.h"
#include <iostream>

Scene* GameScene::createScene(){
    Scene* myScene = Scene::create();
    GameScene* myLayer = GameScene::create();
    myScene->addChild(myLayer);
    return myScene;
}

bool GameScene::init(){
    if ( !Layer::init() ){
        return false;
    }

	board = new Board();

    TMXTiledMap* gameMap = TMXTiledMap::create("gameMap.tmx");
    this->addChild(gameMap);
    board->initPieces(gameMap);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event)->void{
        Point clickPos =Director::getInstance()->convertToGL(touch->getLocationInView());
        PointXY chosenBlock = PointXY((int)clickPos.x / 80 - 1, 7 - (int)clickPos.y / 70);
        std::cout<<chosenBlock.x<<","<<chosenBlock.y<<"."<<std::endl;

		if (chosenBlock.x < 0 || chosenBlock.y < 0)
			return;
		if (chosenBlock.x > 8 || chosenBlock.y>6)
			return;
		auto clickedPiece = board->getPiece(chosenBlock);

		// if no piece has been choosen yet
		if (board->selected->getType() == Pieces::NIL) {
			// cannot choose opponent's piece
			if (board->currentPlayer != clickedPiece->getPlayer())
				return;
			//  choose this piece and highlight it
			board->selected = clickedPiece;
			// if the piece exists, highlight
			if(clickedPiece->getType() != Pieces::NIL)
				clickedPiece->highlight();
		} else {
			PointXY from = board->selected->getPositionBlock();
			if (board->availableMove(Move{ from,chosenBlock })) {
				//move
				board->moveChess(board->selected, chosenBlock);
			} else {
				//reset
				board->selected->recover();
				board->selected = board->nul_piece;
			}
		}
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  
    return true;
}
