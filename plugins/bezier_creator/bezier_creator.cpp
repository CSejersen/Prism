#include "env.h"
#include "raylib.h"
#include "raymath.h"
#include "step_functions.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern "C" {

const float AxisLength = 500;
const float PointRadius = 10;
const Color PointHoverCol = BLUE;
const float PointsOnCurve = 30;
const int FlashDuration = 5;
Color PointCol = RED;

struct point {
  Vector2 center;
  bool hovered;
};

class PlugState {
public:
  std::vector<point> points;
  Camera2D camera;
  point *draggedPoint;

  Color background;
  Font metropolisRegular;
  int flashOnCopyDuration;
};

static PlugState *p = nullptr;

void loadResources() {
  if (FileExists("/Users/sejersen/dev/prism/assets/fonts/metropolis/"
                 "Metropolis-Regular.otf")) {
    p->metropolisRegular = LoadFont("/Users/sejersen/dev/prism/assets/fonts/"
                                    "metropolis/Metropolis-Regular.otf");
  } else {
    std::cerr << "Font file not found!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

void unloadResources() {
  if (p->metropolisRegular.texture.id != 0) {
    UnloadFont(p->metropolisRegular);
  }
}

void plugReset(){
  p->points[0].center = {0, 0};
  p->points[2].center = {AxisLength / 2, -AxisLength}; // 1
  p->points[3].center = {AxisLength, -AxisLength};
  p->points[1].center = {AxisLength / 2, 0}; // 3
  p->flashOnCopyDuration = FlashDuration;
}

char *Vector2ToString(const Vector2 &vec) {
  // Allocate a buffer large enough to hold the string representation
  char *buffer = new char[50];
  snprintf(buffer, 50, "(%.2f, %.2f)", vec.x, vec.y);
  return buffer;
}

void plugInit() {
  p = new PlugState();

  loadResources();
  p->draggedPoint = nullptr;
  p->background = GetColor(0x181818FF);
  p->camera.zoom = 1.0f;

  for (int i = 0; i < 4; i++) {
    p->points.push_back(point());
  }
  plugReset();

  std::cout << "-------------------" << std::endl;
  std::cout << "Initialized Plugin!" << std::endl;
  std::cout << "-------------------" << std::endl;
}

// For hot reloading
void *plugSaveState() {
  TraceLog(LOG_INFO, "Saving state, size = %u", sizeof(*p));
  unloadResources();
  return p;
}

void plugLoadState(void *state) {
  p = static_cast<PlugState *>(state);
  TraceLog(LOG_INFO, "Loading state, size = %u", sizeof(*p));
  loadResources();
}

// gets called every frame
void plugUpdate(Env *env) {
  // Copy the bezier curve points
  if (IsKeyPressed(KEY_C)) {
    char bezier[200];
    snprintf(bezier, 200,
             "{%.3f, %.3f}, {%.3f, %.3f}, {%.3f, %.3f}, {%.3f, %.3f}",
             abs(p->points[0].center.x / AxisLength),
             abs(p->points[0].center.y / AxisLength),
             abs(p->points[1].center.x / AxisLength),
             abs(p->points[1].center.y / AxisLength),
             abs(p->points[2].center.x / AxisLength),
             abs(p->points[2].center.y / AxisLength),
             abs(p->points[3].center.x / AxisLength),
             abs(p->points[3].center.y / AxisLength));
    SetClipboardText(bezier);
    PointCol = GREEN;
  } else {
    if (p->flashOnCopyDuration == 0) {
      PointCol = RED;
      p->flashOnCopyDuration = FlashDuration;
    } else {
      p->flashOnCopyDuration--;
    }
  }

  ClearBackground(p->background);
  p->camera.offset = {env->getScreenWidth() / 2 - AxisLength / 2,
                      env->getScreenHeight() / 2 + AxisLength / 2};
  BeginMode2D(p->camera);

  // Square
  DrawLineEx({0, 0}, {0, -AxisLength}, 1, GRAY);
  DrawLineEx({0, 0}, {AxisLength, 0}, 1, GRAY);
  DrawLineEx({0, -AxisLength}, {AxisLength, -AxisLength}, 1, GRAY);
  DrawLineEx({AxisLength, -AxisLength}, {AxisLength, 0}, 1, GRAY);

  Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), p->camera);

  if (IsKeyPressed(KEY_SPACE)) {
    plugReset();
  }

  DrawTextEx(p->metropolisRegular, "Cubic Bezier Points:",
             {-(env->getScreenWidth()) / 4, -AxisLength}, 15, 3, WHITE);

  for (int i = 0; i < 4; i++) {
    Vector2 normalizedPoint =
        Vector2Scale(p->points[i].center, 1.0f / AxisLength);
    normalizedPoint.x = abs(normalizedPoint.x);
    normalizedPoint.y = abs(normalizedPoint.y);
    char *pointStr = Vector2ToString(normalizedPoint);

    DrawTextEx(p->metropolisRegular, pointStr,
               {-(env->getScreenWidth()) / 4, -AxisLength + 20 * (i + 1)}, 15, 3,
               WHITE);

    delete[] pointStr;
  }

  DrawLineEx(p->points[0].center, p->points[1].center, 2, WHITE);
  DrawLineEx(p->points[2].center, p->points[3].center, 2, WHITE);

  for (auto &point : p->points) {
    if (CheckCollisionPointCircle(mouse, point.center, PointRadius)) {
      point.hovered = true;
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        p->draggedPoint = &point;
      }
    } else {
      point.hovered = false;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      p->draggedPoint = nullptr;
    }

    if (p->draggedPoint) {
      p->draggedPoint->center.x = mouse.x;
      p->draggedPoint->center.y = mouse.y;
    }

    if (point.hovered || &point == p->draggedPoint)
      DrawCircleV(point.center, PointRadius, PointHoverCol);
    else {
      DrawCircleV(point.center, PointRadius, PointCol);
    }
  }

  CubicBezier bezier(p->points[0].center, p->points[1].center,
                     p->points[2].center, p->points[3].center);

  DrawSplineSegmentBezierCubic(bezier.p1, bezier.p2, bezier.p3, bezier.p4, 2,
                               WHITE);
  for (int i = 1; i < PointsOnCurve; i++) {
    float t = i / PointsOnCurve;
    Vector2 p = GetSplinePointBezierCubic(bezier.p1, bezier.p2, bezier.p3,
                                          bezier.p4, t);
    DrawCircleV(p, 4, WHITE);
  }
}

bool plugFinished() { return true; }
}
