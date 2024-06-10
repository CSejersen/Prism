#include "ffmpeg.h"
#include "raylib.h"
#include <cstdlib>
#include <iostream>

extern "C" {

const float RenderWidth = 1600;
const float RenderHeight = 900;
const float RenderFPS = 30;
const float RenderDeltaT = 1 / RenderFPS;

class PlugState {
public:
  ffmpeg *ffmpeg;
  float renderDuration;
  RenderTexture2D screen;

  Camera2D camera;
  Color background;
  
  // Assets below
};

static PlugState *p = nullptr;

void loadResources() {
  p->screen = LoadRenderTexture(RenderWidth, RenderHeight);
}

void unloadResources() { UnloadRenderTexture(p->screen); }

void plugInit() {
  p = new PlugState();

  loadResources();

  p->ffmpeg = nullptr;
  p->renderDuration = 0;
  p->camera.zoom = 1.0f;

  p->background = GetColor(0x181818FF);

  std::cout << "-------------------" << std::endl;
  std::cout << "Initialized Plugin!" << std::endl;
  std::cout << "-------------------" << std::endl;
}

void PROJECT_NAME(float dt, float screenWidth, float screenHeight) { 
  DrawText("PROJECT_NAME", screenWidth/2, screenHeight/2, 20, WHITE);
}

// For hot reloading
void *plugSaveState() {
  unloadResources();
  return p;
}

void plugLoadState(void *state) {
  p = static_cast<PlugState *>(state);
  loadResources();
}

// Gets called every frame DON'T CHANGE
void plugUpdate() {
  BeginDrawing();

  // RENDERING MODE
  if (p->ffmpeg) {
    TraceLog(LOG_INFO, "SWITCHED TO RENDERING MODE");
    SetTraceLogLevel(LOG_WARNING);
    // Stop rendering if duration is reached
    if (p->renderDuration >= 10) {
      p->ffmpeg->endRendering();
      delete p->ffmpeg;
      p->ffmpeg = nullptr;
    } else { // Render a frame and send to ffmpeg proc
      BeginTextureMode(p->screen);
      PROJECT_NAME(RenderDeltaT, RenderWidth, RenderHeight);
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
      PROJECT_NAME(GetFrameTime(), GetScreenWidth(), GetScreenHeight());
    }
  }
  EndDrawing();
}
}
