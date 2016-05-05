//
//  PopUpLayer.h
//  Animal
//
//  Created by yang_xiong on 16/4/6.
//
//

#ifndef PopUpLayer_h
#define PopUpLayer_h
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class PopUpLayer: public cocos2d::Layer{
public:
 
    static PopUpLayer* createPop();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PopUpLayer);
    void onOKClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    
};

#endif /* PopUpLayer_h */
