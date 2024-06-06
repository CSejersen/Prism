#include "../../src/ffmpeg.h"
#include "../../src/interpolator.h"
#include "raylib.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

extern "C" {

const int squareNum = 4;
const float squareHeight = 100;
const float squareWidth = 100;
const float SquarePadding = 20;
const float RenderWidth = 1600;
const float RenderHeight = 900;
const float RenderFPS = 30;
const float RenderDeltaT = 1 / RenderFPS;

enum SquareState {
  s1 = 0,
  s2,
  s3,
  s4,
};

class Square {
public:
  Square(int s) {
    switch (s) {
    case 1:
      currentIndex = 0;
      targetIndex = 0;
      state = s1;
      break;
    case 2:
      currentIndex = 1;
      targetIndex = 0;
      state = s2;
      break;
    case 3:
      currentIndex = 0;
      targetIndex = 1;
      state = s3;
      break;
    case 4:
      currentIndex = 1;
      targetIndex = 1;
      state = s4;
    }
  }

  void updatePosition(float t) {
    switch (state) {
    case s1:
      posX = 0 + (t * (squareWidth + SquarePadding));
      posY = 0;
      break;
    case s2:
      posX = squareWidth + SquarePadding;
      posY = 0 + (t * (squareHeight + SquarePadding));
      break;
    case s3:
      posX = squareWidth + SquarePadding - (t * (squareHeight + SquarePadding));
      posY = squareHeight + SquarePadding;
      break;
    case s4:
      posX = 0;
      posY =
          squareHeight + SquarePadding - (t * (squareHeight + SquarePadding));
      break;
    }
  }
  int currentIndex;
  int targetIndex;
  SquareState state;
  float posX;
  float posY;
  Color color;

private:
};

class PlugState {
public:
  Interpolator interp;
  bool tasksInitialized;
  ffmpeg *ffmpeg;
  RenderTexture2D screen;
  float renderDuration;

  Color background;
  std::vector<Square> squares;
};

static PlugState *p = nullptr;

void squareRotation(Interpolator &t, float dt, int screenWidth,
                    int screenHeight) {
  t.update(dt);
  ClearBackground(p->background);
  /* DrawRectangle(0, 0, 100, 100, RED); */
  for (int i = 0; i < 4; i++) {
    p->squares[i].updatePosition(t.getValue());
    /* TraceLog(LOG_INFO, "Updated Square positio posX = %f, posY = %f",
     * squares[i].posX, squares[i].posY); */
    float posX = p->squares[i].posX + (screenWidth * 0.5) -
                 (squareWidth + SquarePadding);
    float posY = p->squares[i].posY + (screenHeight * 0.5) -
                 (squareHeight + SquarePadding);
    DrawRectangle(posX, posY, squareWidth, squareHeight, RED);
  }
}

void plugInit() {
  p = new PlugState();
  p->background = GetColor(0x181818FF);
  p->tasksInitialized = false;
  p->ffmpeg = nullptr;
  p->renderDuration = 0;

  p->screen = LoadRenderTexture(RenderWidth, RenderHeight);
  // create the squares
  for (int i = 0; i < squareNum; i++) {
    p->squares.emplace_back(i + 1);
  }

  std::cout << "-------------------" << std::endl;
  std::cout << "Initialized Plugin!" << std::endl;
  std::cout << "-------------------" << std::endl;
}

// For hot reloading
void *plugSaveState() { return p; }
void plugLoadState(void *state) {
  p = static_cast<PlugState *>(state);
  p->tasksInitialized = false;
}

// gets called every frame
void plugUpdate() {
  if (!p->tasksInitialized) {
    p->interp.clearTasks();

    // ANIMATION STEPS
    p->interp.addTask({0, 1, 1});
    p->interp.addTask({1, 0, 1});

    p->tasksInitialized = true;
  }

  BeginDrawing();

  // RENDERING MODE
  if (p->ffmpeg) {
    TraceLog(LOG_INFO, "RENDERING MODE");
    SetTraceLogLevel(LOG_WARNING);
    if (p->renderDuration >= 10){
      p->ffmpeg->endRendering();
      delete p->ffmpeg;
      p->ffmpeg = nullptr;
    } else {
      BeginTextureMode(p->screen);
      squareRotation(p->interp, RenderDeltaT, RenderWidth, RenderHeight);
      p->renderDuration += RenderDeltaT;
      EndTextureMode();

      Image image = LoadImageFromTexture(p->screen.texture);

      if (!p->ffmpeg->sendFrameFlipped(image.data, image.width, image.height)) {
        p->ffmpeg->endRendering();
        delete p->ffmpeg;
        p->ffmpeg = nullptr;
        p->interp.reset();
      }
      UnloadImage(image);
    }
  } else {
    if (IsKeyPressed(KEY_M)) {
      p->renderDuration = 0;
      p->interp.reset();
      p->ffmpeg = ffmpeg::startRendering(RenderWidth, RenderHeight, RenderFPS);
    } else {
      squareRotation(p->interp, GetFrameTime(), GetScreenWidth(),
                     GetScreenHeight());
      /* DrawRectangle(0, 0, 100, 100, RED); */
    }
  }
  EndDrawing();
}
}
