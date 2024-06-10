#include "plug.h"
#include "raylib.h"
#include <dlfcn.h> // load dll
#include <iostream>

char* libPlugPath;
 
void *libPlug = nullptr;

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
  plugUpdate = (void (*)())dlsym(libPlug, "plugUpdate");

  // Check for errors
  char *error;
  if ((error = dlerror()) != nullptr) {
    std::cerr << "Failed to get the function addresses: " << error << std::endl;
    dlclose(libPlug);
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <library_path>" << std::endl;
    return 1;
  }

  // Extract the library path from command-line argument
  libPlugPath = argv[1];

  const int screenWidth = 1600;
  const int screenHeight = 900;

  if (!libPlugReload()) {
    return 1;
  }

  InitWindow(screenWidth, screenHeight, "PRISM");
  plugInit();
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Hot reloading
    if (IsKeyPressed(KEY_R)) {
      void *state = plugSaveState();
      if (!libPlugReload()) {
        std::cout << "ERROR: Failed to reload libplug" << std::endl;
        return 1;
      }
      plugLoadState(state);
    }

    plugUpdate();
  }

  CloseWindow();

  return 0;
}
