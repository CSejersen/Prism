#include "plug.h"
#include "raylib.h"
#include <dlfcn.h> // load dll
#include <iostream>

char libPlugPath[] = "/Users/sejersen/dev/prism/dlls/libplugin.so";
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

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  if (!libPlugReload()) {
    return 1;
  }

  InitWindow(screenWidth, screenHeight, "PRISM WINDOW");
  plugInit();
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Hot reloading 
    if(IsKeyPressed(KEY_R)){
      void *state = plugSaveState();
      if(!libPlugReload()){
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
