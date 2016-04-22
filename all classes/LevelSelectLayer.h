//
//  LevelSelectLayer.h
//  Animal
//
//  Created by yang_xiong on 16/4/13.
//
//

#ifndef LevelSelectLayer_h
#define LevelSelectLayer_h

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
class LevelSelectLayer: public cocos2d::Layer{
public:
    cocos2d::ui::Button* PVPButton;
    cocos2d::ui::Button* PVMinimaxButton;
    cocos2d::ui::Button* PVMTCSButton;
    cocos2d::ui::Button* MinimaxVMTCSButton;
    
    static LevelSelectLayer* createSelect();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelSelectLayer);
    void onPVPButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    void onPVMinimaxButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    void onPVMTCSButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    void onMinimaxVMTCSButtonClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    
};

#endif /* LevelSelectLayer_h */
