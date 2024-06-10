#include "ffmpeg.h"
#include "step_functions.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern "C" {

const float RenderWidth = 1600;
const float RenderHeight = 900;
const float RenderFPS = 30;
const float RenderDeltaT = 1 / RenderFPS;
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
  size_t size;
  ffmpeg *ffmpeg;
  RenderTexture2D screen;
  float renderDuration;
  std::vector<point> points;
  Camera2D camera;
  point *draggedPoint;

  Color background;
  Font metropolisRegular;
  Color test;
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

  p->screen = LoadRenderTexture(RenderWidth, RenderHeight);
}

void unloadResources() {
  if (p->metropolisRegular.texture.id != 0) {
    UnloadFont(p->metropolisRegular);
  }
  UnloadRenderTexture(p->screen);
}

void resetPoints() {
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

void bezierCreator(float dt, float screenWidth, float screenHeight) {
  // Copy the bezier curve points
  if (IsKeyPressed(KEY_C)) {
    char bezier[200];
    snprintf(
        bezier, 200, "{%.2f, %.2f}, {%.2f, %.2f}, {%.2f, %.2f}, {%.2f, %.2f}",
        abs(p->points[0].center.x/AxisLength), abs(p->points[0].center.y/AxisLength), 
        abs(p->points[1].center.x/AxisLength), abs(p->points[1].center.y/AxisLength), 
        abs(p->points[2].center.x/AxisLength), abs(p->points[2].center.y/AxisLength), 
        abs(p->points[3].center.x/AxisLength), abs(p->points[3].center.y/AxisLength));
    SetClipboardText(bezier);
    PointCol = GREEN;
  }
  else {
    if (p->flashOnCopyDuration == 0){
      PointCol = RED;
      p->flashOnCopyDuration = FlashDuration;
    } else {
      p->flashOnCopyDuration--;
    }
  }

  ClearBackground(p->background);
  p->camera.offset = {screenWidth / 2 - AxisLength / 2,
                      screenHeight / 2 + AxisLength / 2};
  BeginMode2D(p->camera);

  // Square
  DrawLineEx({0, 0}, {0, -AxisLength}, 1, GRAY);
  DrawLineEx({0, 0}, {AxisLength, 0}, 1, GRAY);
  DrawLineEx({0, -AxisLength}, {AxisLength, -AxisLength}, 1, GRAY);
  DrawLineEx({AxisLength, -AxisLength}, {AxisLength, 0}, 1, GRAY);

  Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), p->camera);

  if (IsKeyPressed(KEY_SPACE)) {
    resetPoints();
  }

  DrawTextEx(p->metropolisRegular,
             "Cubic Bezier Points:", {-screenWidth / 4, -AxisLength}, 15, 3,
             WHITE);

  for (int i = 0; i < 4; i++) {
    Vector2 scaledPoint = Vector2Scale(p->points[i].center, 1.0f/AxisLength);
    scaledPoint.x = abs(scaledPoint.x);
    scaledPoint.y = abs(scaledPoint.y);
    char *pointStr = Vector2ToString(scaledPoint);

    DrawTextEx(p->metropolisRegular, pointStr,
               {-screenWidth / 4, -AxisLength + 20 * (i + 1)}, 15, 3, WHITE);

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

  CubicBezier bezier(p->points[0].center, p->points[1].center, p->points[2].center, p->points[3].center);

  DrawSplineSegmentBezierCubic(bezier.p1, bezier.p2, bezier.p3, bezier.p4, 2, WHITE);
  for (int i = 1; i < PointsOnCurve; i++) {
    float t = i / PointsOnCurve;
    Vector2 p = GetSplinePointBezierCubic(bezier.p1, bezier.p2, bezier.p3,
                                          bezier.p4, t);
    DrawCircleV(p, 4, WHITE);
  }
}

void plugInit() {
  p = new PlugState();

  loadResources();

  p->ffmpeg = nullptr;
  p->renderDuration = 0;
  p->draggedPoint = nullptr;

  p->background = GetColor(0x181818FF);
  p->camera.zoom = 1.0f;
  p->size = sizeof(*p);

  for (int i = 0; i < 4; i++) {
    p->points.push_back(point());
  }
  resetPoints();

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
void plugUpdate() {
  BeginDrawing();

  // RENDERING MODE
  if (p->ffmpeg) {
    TraceLog(LOG_INFO, "RENDERING MODE");
    SetTraceLogLevel(LOG_WARNING);
    // Stop rendering if duration is reached
    if (p->renderDuration >= 10) {
      p->ffmpeg->endRendering();
      delete p->ffmpeg;
      p->ffmpeg = nullptr;
    } else { // Render a frame and send to ffmpeg proc
      BeginTextureMode(p->screen);
      bezierCreator(RenderDeltaT, RenderWidth, RenderHeight);
      p->renderDuration += RenderDeltaT;
      EndTextureMode();

      Image image = LoadImageFromTexture(p->screen.texture);

      if (!p->ffmpeg->sendFrameFlipped(image.data, image.width, image.height)) {
        p->ffmpeg->endRendering();
        delete p->ffmpeg;
        p->ffmpeg = nullptr;
      }
      UnloadImage(image);
    }

    // PREVIEW MODE
  } else {
    if (IsKeyPressed(KEY_M)) {
      p->renderDuration = 0;
      p->ffmpeg = ffmpeg::startRendering(RenderWidth, RenderHeight, RenderFPS);
    } else {
      bezierCreator(GetFrameTime(), GetScreenWidth(), GetScreenHeight());
    }
  }
  EndDrawing();
}
}
