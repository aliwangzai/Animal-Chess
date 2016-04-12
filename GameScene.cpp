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

void GameScene::moveChess(Pieces *fromPiece, Point to, Pieces* toPiece){
    Point from = fromPiece->getPositionBlock();
    if((to.x>from.x && fromPiece->getSprite()->isFlippedX()) ||
       (to.x<from.x && !fromPiece->getSprite()->isFlippedX()))
        fromPiece->changeDirection();
    fromPiece->setPositionBlock(to);
    fromPiece->setPosition((to.x+1)*80+40, (7-to.y)*70+35);
    if(toPiece!=nullptr){
        if(fromPiece->getType()>toPiece->getType()){
            fromPiece->recover();
            BoardPiece.erase(BoardPiece.begin()+toIndex);
            toPiece->removeFromParent();
            }
        else if(fromPiece->getType()<toPiece->getType()){
            BoardPiece.erase(BoardPiece.begin()+fromIndex);
            fromPiece->removeFromParent();
            }
        else{
             BoardPiece.erase(BoardPiece.begin()+toIndex);
             BoardPiece.erase(BoardPiece.begin()+fromIndex);
            toPiece->removeFromParent();
            fromPiece->removeFromParent();
         
        }
    }
}

bool moveable(Point from,Point to){
    return true;
}

void GameScene::initPieces(TMXTiledMap* map){
    TMXObjectGroup* objgroup = map->getObjectGroup("Animals");
    
    float x,y;
    Sprite* elephantSprite = Sprite::create("elephant.png");
    Sprite* lionSprite = Sprite::create("lion.png");
    Sprite* tigerSprite = Sprite::create("tiger.png");
    Sprite* leopardSprite = Sprite::create("leopard.png");
    Sprite* dogSprite = Sprite::create("dog.png");
    Sprite* wolfSprite = Sprite::create("wolf.png");
    Sprite* catSprite = Sprite::create("cat.png");
    Sprite* ratSprite = Sprite::create("rat.png");
    
    Sprite* elephantSprite2 = Sprite::create("elephant.png");
    Sprite* lionSprite2 = Sprite::create("lion.png");
    Sprite* tigerSprite2 = Sprite::create("tiger.png");
    Sprite* leopardSprite2 = Sprite::create("leopard.png");
    Sprite* dogSprite2 = Sprite::create("dog.png");
    Sprite* wolfSprite2 = Sprite::create("wolf.png");
    Sprite* catSprite2 = Sprite::create("cat.png");
    Sprite* ratSprite2 = Sprite::create("rat.png");
    
    ValueMap elephant1Pos = objgroup->getObject("elephant1");
    ValueMap lion1Pos = objgroup->getObject("lion1");
    ValueMap tiger1Pos = objgroup->getObject("tiger1");
    ValueMap leopard1Pos = objgroup->getObject("leopard1");
    ValueMap dog1Pos = objgroup->getObject("dog1");
    ValueMap wolf1Pos = objgroup->getObject("wolf1");
    ValueMap cat1Pos = objgroup->getObject("cat1");
    ValueMap rat1Pos = objgroup->getObject("rat1");
    
    ValueMap elephant2Pos = objgroup->getObject("elephant2");
    ValueMap lion2Pos = objgroup->getObject("lion2");
    ValueMap tiger2Pos = objgroup->getObject("tiger2");
    ValueMap leopard2Pos = objgroup->getObject("leopard2");
    ValueMap dog2Pos = objgroup->getObject("dog2");
    ValueMap wolf2Pos = objgroup->getObject("wolf2");
    ValueMap cat2Pos = objgroup->getObject("cat2");
    ValueMap rat2Pos = objgroup->getObject("rat2");
    
    Pieces* elephantPiece1 = Pieces::create();
    elephantPiece1->bindSprite(elephantSprite);
    x = elephant1Pos.at("x").asFloat();
    y = elephant1Pos.at("y").asFloat();
    elephantPiece1->setPosition(Point(x,y));
    elephantPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::ELEPHANT);
    //std::cout<<elephant1Pos.at("x").asFloat()<<","<<elephant1Pos.at("y").asFloat();
    
    Pieces* lionPiece1 = Pieces::create();
    lionPiece1->bindSprite(lionSprite);
    x = lion1Pos.at("x").asFloat();
    y = lion1Pos.at("y").asFloat();
    lionPiece1->setPosition(Point(x,y));
    lionPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::LION);
    
    Pieces* tigerPiece1 = Pieces::create();
    tigerPiece1->bindSprite(tigerSprite);
    x = tiger1Pos.at("x").asFloat();
    y = tiger1Pos.at("y").asFloat();
    tigerPiece1->setPosition(Point(x,y));
    tigerPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::TIGER);
    
    Pieces* leopardPiece1 = Pieces::create();
    leopardPiece1->bindSprite(leopardSprite);
    x = leopard1Pos.at("x").asFloat();
    y = leopard1Pos.at("y").asFloat();
    leopardPiece1->setPosition(Point(x,y));
    leopardPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::LEOPARD);
    
    Pieces* dogPiece1 = Pieces::create();
    dogPiece1->bindSprite(dogSprite);
    x = dog1Pos.at("x").asFloat();
    y = dog1Pos.at("y").asFloat();
    dogPiece1->setPosition(Point(x,y));
    dogPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::DOG);

    Pieces* wolfPiece1 = Pieces::create();
    wolfPiece1->bindSprite(wolfSprite);
    x = wolf1Pos.at("x").asFloat();
    y = wolf1Pos.at("y").asFloat();
    wolfPiece1->setPosition(Point(x,y));
    wolfPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::WOLF);
    
    Pieces* catPiece1 = Pieces::create();
    catPiece1->bindSprite(catSprite);
    x = cat1Pos.at("x").asFloat();
    y = cat1Pos.at("y").asFloat();
    catPiece1->setPosition(Point(x,y));
    catPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::CAT);

    Pieces* ratPiece1 = Pieces::create();
    ratPiece1->bindSprite(ratSprite);
    x = rat1Pos.at("x").asFloat();
    y = rat1Pos.at("y").asFloat();
    ratPiece1->setPosition(Point(x,y));
    ratPiece1->setProperty(Point((int)x/80-1,7-(int)y/70), 0, Pieces::RAT);

    
    Pieces* elephantPiece2 = Pieces::create();
    elephantSprite2->setFlippedX(true);
    elephantPiece2->bindSprite(elephantSprite2);
    x = elephant2Pos.at("x").asFloat();
    y = elephant2Pos.at("y").asFloat();
    elephantPiece2->setPosition(Point(x,y));
    elephantPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::ELEPHANT);
    
    Pieces* lionPiece2 = Pieces::create();
    lionSprite2->setFlippedX(true);
    lionPiece2->bindSprite(lionSprite2);
    x = lion2Pos.at("x").asFloat();
    y = lion2Pos.at("y").asFloat();
    lionPiece2->setPosition(Point(x,y));
    lionPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::LION);
    
    Pieces* tigerPiece2 = Pieces::create();
    tigerSprite2->setFlippedX(true);
    tigerPiece2->bindSprite(tigerSprite2);
    x = tiger2Pos.at("x").asFloat();
    y = tiger2Pos.at("y").asFloat();
    tigerPiece2->setPosition(Point(x,y));
    tigerPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::TIGER);
    
    Pieces* leopardPiece2 = Pieces::create();
    leopardSprite2->setFlippedX(true);
    leopardPiece2->bindSprite(leopardSprite2);
    x = leopard2Pos.at("x").asFloat();
    y = leopard2Pos.at("y").asFloat();
    leopardPiece2->setPosition(Point(x,y));
    leopardPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::LEOPARD);

    
    Pieces* dogPiece2 = Pieces::create();
    dogSprite2->setFlippedX(true);
    dogPiece2->bindSprite(dogSprite2);
    x = dog2Pos.at("x").asFloat();
    y = dog2Pos.at("y").asFloat();
    dogPiece2->setPosition(Point(x,y));
    dogPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::DOG);
    
    Pieces* wolfPiece2 = Pieces::create();
    wolfSprite2->setFlippedX(true);
    wolfPiece2->bindSprite(wolfSprite2);
    x = wolf2Pos.at("x").asFloat();
    y = wolf2Pos.at("y").asFloat();
    wolfPiece2->setPosition(Point(x,y));
    wolfPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::WOLF);
    
    Pieces* catPiece2 = Pieces::create();
    catSprite2->setFlippedX(true);
    catPiece2->bindSprite(catSprite2);
    x = cat2Pos.at("x").asFloat();
    y = cat2Pos.at("y").asFloat();
    catPiece2->setPosition(Point(x,y));
    catPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::CAT);
    
    Pieces* ratPiece2 = Pieces::create();
    ratSprite2->setFlippedX(true);
    ratPiece2->bindSprite(ratSprite2);
    x = rat2Pos.at("x").asFloat();
    y = rat2Pos.at("y").asFloat();
    ratPiece2->setPosition(Point(x,y));
    ratPiece2->setProperty(Point((int)x/80-1,7-(int)y/70), 1, Pieces::RAT);

    
    map->addChild(elephantPiece1);
    map->addChild(lionPiece1);
    map->addChild(tigerPiece1);
    map->addChild(leopardPiece1);
    map->addChild(dogPiece1);
    map->addChild(wolfPiece1);
    map->addChild(catPiece1);
    map->addChild(ratPiece1);
    map->addChild(elephantPiece2);
    map->addChild(lionPiece2);
    map->addChild(tigerPiece2);
    map->addChild(leopardPiece2);
    map->addChild(dogPiece2);
    map->addChild(wolfPiece2);
    map->addChild(catPiece2);
    map->addChild(ratPiece2);
    
    BoardPiece.pushBack(elephantPiece1);
    BoardPiece.pushBack(lionPiece1);
    BoardPiece.pushBack(tigerPiece1);
    BoardPiece.pushBack(leopardPiece1);
    BoardPiece.pushBack(dogPiece1);
    BoardPiece.pushBack(wolfPiece1);
    BoardPiece.pushBack(catPiece1);
    BoardPiece.pushBack(ratPiece1);
    BoardPiece.pushBack(elephantPiece2);
    BoardPiece.pushBack(lionPiece2);
    BoardPiece.pushBack(tigerPiece2);
    BoardPiece.pushBack(leopardPiece2);
    BoardPiece.pushBack(dogPiece2);
    BoardPiece.pushBack(wolfPiece2);
    BoardPiece.pushBack(catPiece2);
    BoardPiece.pushBack(ratPiece2);

}


