#include "cocos2d.h"
#include "Ship.h"

using namespace cocos2d;

void Ship::stop(void) {
  memset(&(this->vel), 0, sizeof(point2D));
}

void Ship::updateThrustPos(void) {
  if (this->pThrust) {
    CCRect bbox = this->boundingBox();
    CCRect thrustBBox = this->pThrust->boundingBox();
    float shipMidX = (bbox.getMaxX() - bbox.getMinX()) * 0.5f;
    float shipMidY = (bbox.getMaxY() - bbox.getMinY()) * 0.5f;
    float thrustSizeY = (thrustBBox.getMaxY() - thrustBBox.getMinY()) * 0.5f;
    pThrust->setPosition(ccp(shipMidX, -shipMidY * 0.0f - thrustSizeY));
  }
}

void Ship::update(float dt, bool bThrusting, point2D& rGravity) {
  float newVx = this->vel.x + rGravity.x * dt;
  float newVy = this->vel.y + rGravity.y * dt;

  if (bThrusting) {
    float thrustAngle = CC_DEGREES_TO_RADIANS(this->getRotation());
    float thrustCos = cosf(thrustAngle);
    float thrustSin = sinf(thrustAngle);
    float accX = THRUST * thrustSin;
    float accY = THRUST * thrustCos;

    newVx += accX * dt;
    newVy += accY * dt;
  }

  if (this->pThrust) {
    this->pThrust->setVisible(bThrusting);

    if (bThrusting) {
      float scalar = (float)(rand() % 100 + rand() % 100 + 2) * 0.5f;
      this->pThrust->setScale(scalar * 0.01);
    }
  }

  float x = this->getPositionX();
  float y = this->getPositionY();

  float aveVx = (this->vel.x + newVx) * 0.5;
  float aveVy = (this->vel.y + newVy) * 0.5;

  x += aveVx * dt;
  y += aveVy * dt;

  this->vel.x = newVx;
  this->vel.y = newVy;

  this->setPosition(ccp(x, y));
}

Ship* Ship::create(const char* pFile) {
  Ship* pShip = new Ship();

  if (pShip && pShip->initWithFile(pFile)) {
    // Set to auto release
    pShip->autorelease();

    // Custom initialization goes here.
    pShip->stop();

    // Add thrust sprite.
    pShip->pThrust = CCSprite::create("thrust.png");
    pShip->pThrust->setVisible(false);
    pShip->pThrust->setAnchorPoint(ccp(0.5f, 1.f));
    pShip->updateThrustPos();

    pShip->addChild(pShip->pThrust);
  }
  else {
    CC_SAFE_DELETE(pShip);
    pShip = NULL;
  }

  return pShip;
}
