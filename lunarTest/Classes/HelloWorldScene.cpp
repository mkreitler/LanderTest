#include "CCScheduler.h"

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "constants.h"
#include "Ship.h"

using namespace cocos2d;
using namespace CocosDenshion;

point2D sGravity(0, -GRAVITY);

// Update Handler /////////////////////////////////////////////////////////////
void HelloWorld::update(float dt) {
    if (this->pPlayer) {
        this->pPlayer->update(dt, this->bThrusting, sGravity);
    }
}

// Event Handlers /////////////////////////////////////////////////////////////
bool HelloWorld::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    this->bThrusting = true;

    return true;
}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    this->bThrusting = false;
}

void HelloWorld::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    this->bThrusting = false;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
}

void HelloWorld::registerWithTouchDispatcher(void) {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, false);
}

///////////////////////////////////////////////////////////////////////////////

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
       pAccelerationValue->x;                //horizontal acceleration
       pAccelerationValue->y;                //vertical acceleration

       if (this->pPlayer) {
        float angle = atan2(pAccelerationValue->y, -pAccelerationValue->x);
        this->pPlayer->setRotation(CC_RADIANS_TO_DEGREES(angle) + 90);
        // CCLog("Angle: %f", angle * 180.f / 3.1415926f);
       }
 }

void HelloWorld::onExit(void) {
    this->setTouchEnabled(false);

    CCLayer::onExit();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Activate accelerometer.
    setAccelerometerEnabled(true);

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    this->pPlayer = Ship::create("ship.png");

    // position the sprite on the center of the screen
    this->pPlayer->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(this->pPlayer, 0);

    // Register for touch events.
    this->setTouchEnabled(true);

    // Schedule an update.
    this->schedule( schedule_selector(HelloWorld::update), PHYSICS_HZ);

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
