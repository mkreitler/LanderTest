#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define   WIDTH       (1024)            // Width of game screen in virtual pixels
#define   HEIGHT      (768)             // Height of game screen in virtual pixels

#define   PHYSICS_HZ  (1.f / 30.f)
#define   GRAVITY     (30.f)            // VPixels per second squared
#define   THRUST      (GRAVITY * 2.5f)  // VPixels per second squared

typedef struct _point2D {
  float x;
  float y;

  _point2D() : x(), y() {}
  _point2D(float xInit, float yInit) : x(xInit), y(yInit) {}

} point2D;

extern point2D sGravity;

#endif // __CONSTANTS_H__
