#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand(time(0));
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    startButton = static_cast<Button*>(rootNode->getChildByName("StartButton"));
    ruleButton = static_cast<Button*>(rootNode->getChildByName("RuleButton"));
    exitButton = static_cast<Button*>(rootNode->getChildByName("ExitButton"));
    earth = static_cast<ImageView*>(rootNode->getChildByName("earth"));
    
    startButton->addTouchEventListener(this, toucheventselector(HelloWorld::onStartClick));
    exitButton->addTouchEventListener(this, toucheventselector(HelloWorld::onExitClick));
    ruleButton->addTouchEventListener(this, toucheventselector(HelloWorld::onRuleClick));
    
    RotateBy * earthRotate = RotateBy::create(20, 360.f);
    RepeatForever* repeatforever = RepeatForever::create(earthRotate);
    earth->runAction(repeatforever);
    
    
    
    return true;
}
void HelloWorld::onRuleClick(cocos2d::Ref *psender,cocos2d::ui::TouchEventType type){
    switch (type) {
        case TOUCH_EVENT_ENDED:{
            PopUpLayer* ruleLayer = PopUpLayer::createPop();
            this->addChild(ruleLayer);
            break;
        }
        default:
            break;
    }
}



void HelloWorld::onExitClick(Ref* pSender,TouchEventType type){
    switch (type) {
        case TOUCH_EVENT_ENDED:
             Director::getInstance()->end();
             #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
             #endif
             break;
        default:
            break;
    }
}
void HelloWorld::onStartClick(Ref *psender,TouchEventType type){
    switch (type) {
        case TOUCH_EVENT_ENDED:{
            LevelSelectLayer* selectLayer = LevelSelectLayer::createSelect();
            this->addChild(selectLayer);
            break;
        }
        default:
            break;
    }
    
}

