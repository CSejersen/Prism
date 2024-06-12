#include <iostream>
#include "raylib.h"
#include "step_functions.h"
#include "env.h"

extern "C" {

const float SquareWaitTime = 0.3;
const float SquareWidth = 70;
const float SquareHeight = 70;
const Color SquareColor = BLUE;
const float SquarePadding = SquareWidth * 0.05;

float SquareMoveTime = 1;

enum SquarePos {
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_RIGHT,
  BOTTOM_LEFT,
};

struct Square {
  SquarePos to;
  float t;
};

class PlugState {
public:
  Color background;

  Square squares[4];
  int nRotations;
};

static PlugState *p = nullptr;

void loadResources() {}

void unloadResources() {}

void toggleSpeed() { SquareMoveTime = SquareMoveTime == 1 ? 0.5 : 1; }

void squareRotation(float dt, float screenWidth, float screenHeight) {
}

void plugInit() {
  p = new PlugState();

  p->background = GetColor(0x181818FF);
  p->squares[0].to = TOP_RIGHT;
  p->squares[1].to = BOTTOM_RIGHT;
  p->squares[2].to = BOTTOM_LEFT;
  p->squares[3].to = TOP_LEFT;

  p->nRotations = 0;

  std::cout << "-------------------" << std::endl;
  std::cout << "Initialized Plugin!" << std::endl;
  std::cout << "-------------------" << std::endl;
}

// For hot reloading
void *plugSaveState() {
  unloadResources();
  return p;
}
void plugLoadState(void *state) {
  loadResources();
  p = static_cast<PlugState *>(state);
}

// gets called every frame
void plugUpdate(Env* env) {
  /* DrawRectangle(0,0,100,100,RED); */
  CubicBezier b({0.000, 0.000}, {0.500, 0.000}, {0.500, 1.000}, {1.000, 1.000});
  CubicBezier sizeB({0.000, 1.000}, {0.387, 0.855}, {0.612, 0.859},
                    {1.000, 1.000});

  ClearBackground(p->background);

  for (Square &sq : p->squares) {
    sq.t = ((sq.t * SquareMoveTime) + env->getDeltaT()) / SquareMoveTime;
    float t = cubicBezierStep(b, sq.t);
    float sizeT = cubicBezierStep(sizeB, sq.t);
    switch (sq.to) {
    case TOP_RIGHT: {
      float posX = (env->getScreenWidth() / 2 - SquareWidth - SquarePadding / 2) +
                   (t * ((2 * SquareWidth) + SquarePadding));
      float posY = (env->getScreenHeight() / 2) - SquareHeight - (SquarePadding / 2);
      DrawRectangle(posX, posY, SquareWidth * sizeT, SquareHeight * sizeT,
                    SquareColor);
      if (sq.t >= 1) {
        sq.to = BOTTOM_RIGHT;
        sq.t = 0;
        p->nRotations++;
        p->nRotations = p->nRotations % 3;
        if (p->nRotations == 0) {
          toggleSpeed();
        }
      }
      break;
    }

    case BOTTOM_RIGHT: {
      float posX = env->getScreenWidth() / 2 + SquareWidth + (SquarePadding / 2);

      float posY = (env->getScreenHeight() / 2) - SquareHeight - (SquarePadding / 2) +
                   t * ((2 * SquareHeight) + SquarePadding);

      DrawRectangle(posX, posY, SquareWidth * sizeT, SquareHeight * sizeT,
                    SquareColor);
      if (sq.t >= 1) {
        sq.to = BOTTOM_LEFT;
        sq.t = 0;
      }
      break;
    }

    case BOTTOM_LEFT: {
      float posX = (env->getScreenWidth() / 2 + SquareWidth + (SquarePadding / 2)) -
                   t * ((2 * SquareWidth) + SquarePadding);
      float posY = (env->getScreenHeight() / 2) + SquareHeight + (SquarePadding / 2);
      DrawRectangle(posX, posY, SquareWidth * sizeT, SquareHeight * sizeT,
                    SquareColor);
      if (sq.t >= 1) {
        sq.to = TOP_LEFT;
        sq.t = 0;
      }
      break;
    }
    case TOP_LEFT:
      float posX = env->getScreenWidth() / 2 - SquareWidth - (SquarePadding / 2);

      float posY = ((env->getScreenHeight() / 2) + SquareHeight + (SquarePadding / 2)) -
                   t * ((2 * SquareHeight) + SquarePadding);

      DrawRectangle(posX, posY, SquareWidth * sizeT, SquareHeight * sizeT,
                    SquareColor);
      if (sq.t >= 1) {
        sq.to = TOP_RIGHT;
        sq.t = 0;
      }
      break;
    }
  }
}

bool plugFinished() { 
  if(p->nRotations > 6){
    return true;
  }
  return false;
}
}
