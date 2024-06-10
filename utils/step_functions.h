#ifndef STEP_FUNCTIONS
#define STEP_FUNCTIONS

#include "raylib.h"

class CubicBezier {
public:
  CubicBezier(Vector2, Vector2, Vector2, Vector2);
  Vector2 p1;
  Vector2 p2;
  Vector2 p3;
  Vector2 p4;
private:
};

float cubicBezierStep(CubicBezier b, float t);

#endif // STEP_FUNCTIONS
