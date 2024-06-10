#include "../../src/ffmpeg.h"
#include "../../src/interpolator.h"
#include "raylib.h"
#include <iostream>

extern "C" {

const float RenderWidth = 1600;
const float RenderHeight = 900;
const float RenderFPS = 30;
const float RenderDeltaT = 1 / RenderFPS;

class PlugState {
public:
  ffmpeg *ffmpeg;
  RenderTexture2D screen;
  float renderDuration;

  Color background;
};

static PlugState *p = nullptr;

void loadResources() {}

void unloadResources() {}

void squareRotation(float dt, int screenWidth, int screenHeight) {
  ClearBackground(p->background);
  DrawRectangle(0, 0, 100, 100, RED);
  
}

void plugInit() {
  p = new PlugState();

  p->ffmpeg = nullptr;
  p->screen = LoadRenderTexture(RenderWidth, RenderHeight);
  p->renderDuration = 0;

  p->background = GetColor(0x181818FF);

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
      squareRotation(RenderDeltaT, RenderWidth, RenderHeight);
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
      squareRotation(GetFrameTime(), GetScreenWidth(), GetScreenHeight());
    }
  }
  EndDrawing();
}
}
