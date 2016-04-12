#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
class HelloWorld : public cocos2d::Layer
{
public:
    cocos2d::ui::ImageView* earth;
    cocos2d::ui::Button* startButton;
    cocos2d::ui::Button* ruleButton;
    cocos2d::ui::Button* exitButton;

    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void onStartClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    void onExitClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
    void onRuleClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__
