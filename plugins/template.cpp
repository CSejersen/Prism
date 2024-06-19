#include <string>
#include "raylib.h"
#include "env.h"

// Avoid C++ namemangeling, needed to link the lib
extern "C" {

class PlugState {
public:
  Color background;
};

static PlugState *p = nullptr;

void loadResources() {}

void unloadResources() {}

void plugReset(){}

void plugInit() {
  p = new PlugState();
}

void *plugSaveState() {
  unloadResources();
  return p;
}
void plugLoadState(void *state) {
  loadResources();
  p = static_cast<PlugState *>(state);
}

void plugUpdate(Env* env) {
  std::string text = "PROJECT_NAME";
  int textWidth = MeasureText(text.c_str(), 20);
  int x = (env->getScreenWidth() - textWidth) / 2;
  int y = env->getScreenHeight() / 2;
  DrawText(text.c_str(), x, y, 20, WHITE);
}

bool plugFinished() { 
  return true;
}
}
