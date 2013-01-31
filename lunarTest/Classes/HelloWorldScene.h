#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Ship;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // Hook for accelerometer
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    // Event Handlers
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

    virtual void registerWithTouchDispatcher(void);
    virtual void onExit(void);

    // Update Handler
    void update(float dt);

private:
  Ship* pPlayer;
  bool  bThrusting;
};

#endif // __HELLOWORLD_SCENE_H__
