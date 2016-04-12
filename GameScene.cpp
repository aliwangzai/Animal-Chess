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
    TMXTiledMap* gameMap = TMXTiledMap::create("gameMap.tmx");
    this->addChild(gameMap);
    initPieces(gameMap);
    
    currentPlayer = 0;
    pieceSelected = nullptr;
    clickNum = 0;
    
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        Point clickPos =Director::getInstance()->convertToGL(touch->getLocationInView());
        Point chosenBlock = Point((int)clickPos.x/80-1,7-(int)clickPos.y/70);
        std::cout<<chosenBlock.x<<","<<chosenBlock.y<<"."<<std::endl;
        
        int index = 0;
        for(index=0 ;index< BoardPiece.size();index++){
            if(BoardPiece.at(index)->getPositionBlock()==chosenBlock){//点击了一个棋子
                if(clickNum == 0){
                    if(BoardPiece.at(index)->getPlayer()==currentPlayer){//第一次点击本方棋子
                        pieceSelected = BoardPiece.at(index);
                        pieceSelected->highlight();
                        clickNum = 1;
                        fromIndex = index;
                    }
                    else{        //第一次点击敌方棋子
                       //do nothing
                    }
                }
                else{
                    if(BoardPiece.at(index)->getPlayer()==currentPlayer){//clickNum==1 //第二次点击本方棋子
                        pieceSelected->recover();
                        pieceSelected = BoardPiece.at(index);
                        pieceSelected->highlight();
                        fromIndex = index;
                    }
                    else{//第二次点击敌方棋子
                        toIndex = index;
                        Pieces * destPiece = BoardPiece.at(index);
                        GameScene::moveChess(pieceSelected,chosenBlock,destPiece);
                        clickNum = 0;
                        toIndex = 0;
                        pieceSelected = nullptr;
                        currentPlayer = (currentPlayer+1)%2;
                    }
                }
                break;
            }
        }
        if(index == BoardPiece.size()){//点击了一个空地
            if(clickNum == 0){}
                //do nothing
            else{
                pieceSelected->recover();
                GameScene::moveChess(pieceSelected,chosenBlock);
                clickNum = 0;
                pieceSelected = nullptr;
                currentPlayer = (currentPlayer+1)%2;
                fromIndex = 0;
                }
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

    return true;
}
