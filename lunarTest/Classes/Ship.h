#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"
#include "constants.h"

class Ship : public cocos2d::CCSprite
{

public:
  static Ship* create(const char* pFile);

  void update(float dt, bool bThrusting, point2D& rGravity);
  void stop(void);
  void updateThrustPos(void);

private:
  point2D vel;
  cocos2d::CCSprite* pThrust;
};

#endif // __SHIP_H__
