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
        PointXY chosenBlock = PointXY(7-(int)clickPos.y/70, (int)clickPos.x / 80 - 1);
        std::cout<<chosenBlock.x<<","<<chosenBlock.y<<"."<<std::endl;
        
		auto clickedPiece = board->getPiece(chosenBlock);
		if (board->currentPlayer == clickedPiece->getPlayer())
			return;
		// if no piece has been choosen
		if (board->selected->getType() == Pieces::NIL) {
			board->selected = clickedPiece;
			// if the piece exists, highlight
			if(clickedPiece->getType() != Pieces::NIL)
				clickedPiece->highlight();
		} else {
			PointXY from = board->selected->getPositionBlock();
			PointXY to = PointXY( chosenBlock.x,chosenBlock.y );
			if (board->availableMove(Move{ from,to })) {
				//move
				board->moveChess(board->selected, chosenBlock, clickedPiece);
				board->currentPlayer = !board->currentPlayer;
			} else {
				//reset
				board->selected->recover();
				board->selected = board->BoardPiece.back();
			}
		}
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  
    return true;
}
