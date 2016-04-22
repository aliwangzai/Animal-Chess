//
//  LevelSelectLayer.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/13.
//
//

#include "LevelSelectLayer.h"
int gameMode;

LevelSelectLayer* LevelSelectLayer::createSelect(){
    LevelSelectLayer* layer = LevelSelectLayer::create();
    return layer;
}

bool LevelSelectLayer::init(){
    if ( !CCLayer::init() ){
        return false;
    }
    auto rootNode = CSLoader::createNode("levelSelect.csb");
    this->addChild(rootNode);
    PVPButton = static_cast<Button*>(rootNode->getChildByName("people_vs_people"));
    PVMinimaxButton = static_cast<Button*>(rootNode->getChildByName("people_vs_minimax"));
    PVMTCSButton = static_cast<Button*>(rootNode->getChildByName("people_vs_MTCS"));
    MinimaxVMTCSButton = static_cast<Button*>(rootNode->getChildByName("minimax_vs_MTCS"));

    PVPButton->addTouchEventListener(this, toucheventselector(LevelSelectLayer::onPVPButtonClick));
    PVMinimaxButton->addTouchEventListener(this, toucheventselector(LevelSelectLayer::onPVMinimaxButtonClick));
    PVMTCSButton->addTouchEventListener(this, toucheventselector(LevelSelectLayer::onPVMTCSButtonClick));
    MinimaxVMTCSButton->addTouchEventListener(this, toucheventselector(LevelSelectLayer::onMinimaxVMTCSButtonClick));

    
    return true;
}
void LevelSelectLayer::onPVPButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
     gameMode = 0;
     Scene* newGame = GameScene::createScene();
     auto transition = TransitionCrossFade::create(0.5f, newGame);
     Director::getInstance()->replaceScene(transition);
}
void LevelSelectLayer::onPVMinimaxButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
    gameMode = 1;
    Scene* newGame = GameScene::createScene();
    auto transition = TransitionCrossFade::create(0.5f, newGame);
    Director::getInstance()->replaceScene(transition);

    
}
void LevelSelectLayer::onPVMTCSButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
    gameMode = 2;
    Scene* newGame = GameScene::createScene();
    auto transition = TransitionCrossFade::create(0.5f, newGame);
    Director::getInstance()->replaceScene(transition);

    
}
void LevelSelectLayer::onMinimaxVMTCSButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
    gameMode = 3;
    Scene* newGame = GameScene::createScene();
    auto transition = TransitionCrossFade::create(0.5f, newGame);
    Director::getInstance()->replaceScene(transition);    
}