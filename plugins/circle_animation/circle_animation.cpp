#include "env.h"
#include "raylib.h"
#include "task.h"

// Avoid C++ name mangling, needed to link the lib
extern "C" {

enum TaskID {
  ID_move = 0,
};

struct Circle {
  Vector2 position;
};

class PlugState {
public:
  Color background;
  Task task;
  bool finished;

  Circle c;
};

static PlugState *p = nullptr;

Task MoveCircle() {
  return TaskSeq::create(TaskMoveVec2::create(&p->c.position, {100, 300}, 3),
                         TaskMoveVec2::create(&p->c.position, {300, 300}, 3),
                         TaskMoveVec2::create(&p->c.position, {300, 100}, 3),
                         TaskMoveVec2::create(&p->c.position, {100, 100}, 3));
}

void loadResources() {}

void unloadResources() {}

void plugReset() {

  if (p != nullptr) {
    delete p;
  }
  p = new PlugState();

  p->c.position = {100, 100};
  p->task = MoveCircle();
  TraceLog(LOG_INFO, "PLUG_RESET: p->task duration : %f",
           static_cast<MoveVec2Data *>(p->task.getData())->duration);
  p->finished = false;
}

void plugInit() {
  taskVTable.rebuild();
  plugReset();
}

void *plugSaveState() {
  unloadResources();
  return p;
}

void plugLoadState(void *state) {
  p = static_cast<PlugState *>(state);
  taskVTable.rebuild();
  loadResources();
}

void plugUpdate(Env env) {

  ClearBackground(p->background);
  DrawCircleV(p->c.position, 50, BLUE);

  p->finished = updateTask(p->task, env);
  TraceLog(LOG_INFO, "p->finisehd = %i", p->finished);
}

bool plugFinished() { return p->finished; }
}
