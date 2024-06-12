#include <CoreServices/CoreServices.h>
#include <dlfcn.h>
#include <iostream>
#include <sys/stat.h>

#include "raylib.h"

#include "env.h"
#include "ffmpeg.h"
#include "plug.h"

// Render settings
const float RenderFPS = 30;
const float RenderWidth = 1920;
const float RenderHeight = 1080;
RenderTexture2D screen;

char *libPlugPath;
struct stat fileInfo;
time_t previousModTime;
void *libPlug = nullptr;
ffmpeg *ffmpeg;

bool libPlugReload() {
  // Close if already open
  if (libPlug != nullptr) {
    dlclose(libPlug);
  }

  // Load shared library
  libPlug = dlopen(libPlugPath, RTLD_NOW);
  if (!libPlug) {
    std::cerr << "ERROR: " << dlerror() << std::endl;
    return false;
  }

  // Reset dlerror()
  dlerror();

  // Get function addresses from DLL
  plugInit = (void (*)())dlsym(libPlug, "plugInit");
  plugSaveState = (void *(*)())dlsym(libPlug, "plugSaveState");
  plugLoadState = (void (*)(void *))dlsym(libPlug, "plugLoadState");
  plugUpdate = (void (*)(Env *))dlsym(libPlug, "plugUpdate");
  plugFinished = (bool (*)())dlsym(libPlug, "plugFinished");

  // Check for errors
  char *error;
  if ((error = dlerror()) != nullptr) {
    std::cerr << "Failed to get the function addresses: " << error << std::endl;
    dlclose(libPlug);
    return false;
  }
  return true;
}

bool isPluginModified() {
  if (fileInfo.st_mtime != previousModTime) {
    previousModTime = fileInfo.st_mtime;
    return true;
  }
  return false;
}

Env *engineInit(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <library_path>" << std::endl;
    exit(1);
  }

  libPlugPath = argv[1];
  previousModTime = fileInfo.st_mtime;

  if (!libPlugReload()) {
    exit(1);
  }

  Env *env = new Env;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(env->getScreenWidth(), env->getScreenHeight(), "PRISM");
  return env;
}

void stopRendering(Env *env) {
  ffmpeg->endRendering();
  delete ffmpeg;
  ffmpeg = nullptr;
  env->setRendering(false);
  SetTraceLogLevel(LOG_INFO);
}

int main(int argc, char *argv[]) {
  Env *env = engineInit(argc, argv);

  screen = LoadRenderTexture(RenderWidth, RenderHeight);
  plugInit();
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // TODO: move hot reloading to it's own thread
    if (stat(libPlugPath, &fileInfo) != 0) {
      std::cerr << "Error: Unable to stat " << libPlugPath << std::endl;
      exit(1);
    }

    // Hot reloading
    if (IsKeyPressed(KEY_H) || isPluginModified()) {
      void *state = plugSaveState();
      if (!libPlugReload()) {
        std::cout << "ERROR: Failed to reload libplug" << std::endl;
        return 1;
      }
      plugLoadState(state);
    }

    if (IsKeyPressed(KEY_R)) {
      env->setScreenWidth(RenderWidth);
      env->setScreenHeight(RenderHeight);
      env->setDeltaT(1 / RenderFPS);
      env->setRendering(true);
      ffmpeg = ffmpeg::startRendering(env->getScreenWidth(),
                                      env->getScreenHeight(), RenderFPS);
    }

    if (env->isRendering()) {
      TraceLog(LOG_INFO, "RENDERING MODE");
      SetTraceLogLevel(LOG_WARNING);
      if (plugFinished()) {
        stopRendering(env);
      } else { // Render a frame and send to ffmpeg proc
        BeginDrawing();
        BeginTextureMode(screen);
        plugUpdate(env);
        EndTextureMode();
        EndDrawing();

        Image image = LoadImageFromTexture(screen.texture);

        if (!ffmpeg->sendFrameFlipped(image.data, image.width, image.height)) {
          stopRendering(env);
        }
        UnloadImage(image);
      }
    } else { // Preview mode
      env->setScreenWidth(GetScreenWidth());
      env->setScreenHeight(GetScreenHeight());
      env->setDeltaT(GetFrameTime());
      BeginDrawing();
      plugUpdate(env);
      EndDrawing();
    }
  }

  CloseWindow();

  return 0;
}
