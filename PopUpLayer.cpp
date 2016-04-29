//
//  PopUpLayer.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/6.
//
//

#include "PopUpLayer.h"
#include <iostream>
using namespace cocos2d::ui;

PopUpLayer* PopUpLayer::createPop(){
    PopUpLayer* layer = PopUpLayer::create();
    return layer;
    
}

bool PopUpLayer::init(){
    if ( !CCLayer::init() ){
        return false;
    }
    auto rootNode = CSLoader::createNode("scrollView.csb");
    this->addChild(rootNode);
    Button* confirmButton = Button::create();
    confirmButton->loadTextures("button_normal2.png", "button_press2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    confirmButton->setPosition(Point(visibleSize.width/2,visibleSize.height/2-220));
    confirmButton->setTitleAlignment(cocos2d::TextHAlignment::CENTER);
    confirmButton->setTitleFontSize(20);
    confirmButton->setTitleText("OK");
    confirmButton->addTouchEventListener(this,toucheventselector(PopUpLayer::onOKClick));
    this->addChild(confirmButton);

    auto callback = [](Touch * ,Event *)
    {
        return true;
    };

    

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
        return true;
   
}

void PopUpLayer::onOKClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
    switch (type) {
        case TOUCH_EVENT_ENDED:{
            this->removeFromParent();
            break;
        }
        default:
            break;
    }
}