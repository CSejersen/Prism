#include "step_functions.h"

CubicBezier::CubicBezier(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4) : p1(p1), p2(p2), p3(p3), p4(p4){}

float cubicBezierStep(CubicBezier b, float t) {
  return GetSplinePointBezierCubic(b.p1, b.p2, b.p3, b.p4, t).y;
}

