#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "env.h"
#include "raylib.h"
#include <vector>

// For accessing Vtable index
extern size_t GroupTag;
extern size_t SeqTag;
extern size_t MoveVec2Tag;

struct TaskFuncs {
  bool (*update)(Env env, void *rawData);
  void (*reset)(Env env, void *rawData);
};

class Task {
public:
  Task() = default;
  Task(size_t id, void *data) : taskID(id), data(data) {}
  size_t taskID;
  void *getData() { return data; }

private:
  void *data;
};

bool updateTask(Task, Env);
void resetTask(Task, Env);

class VTable {
public:
  size_t append(TaskFuncs);
  void rebuild();
  TaskFuncs getFuncs(size_t id);

private:
  std::vector<TaskFuncs> funcs;
};

extern VTable taskVTable;

class TaskGroup {
public:
  static Task create(); // multiple Tasks as arguments
  static bool update(Env env, void *rawData);
  static void reset(Env env, void *rawData);
};

struct GroupData {
  std::vector<Task> tasks;
  float t;
};

class TaskSeq {
public:
  template <class... Args>
  static Task create(Args &&...args); // multiple Tasks as arguments
  static bool update(Env env, void *rawData);
  static void reset(Env env, void *rawData);
};

struct SeqData {
  std::vector<Task> tasks;
  size_t currentTask;
};

template <class... Args> Task TaskSeq::create(Args &&...args) {
  auto *data = new SeqData;
  (data->tasks.push_back(std::forward<Args>(args)), ...);
  data->currentTask = 0;

  return Task(SeqTag, data);
}

// Different task types
class TaskMoveVec2 {
public:
  static Task create(Vector2 *val, Vector2 moveTo, float duration);
  static bool update(Env env, void *rawData);
  static void reset(Env env, void *rawData);
};

struct MoveVec2Data {
  Vector2 *value;
  Vector2 moveTo;
  Vector2 startPos;
  float duration;
  float t;
  bool started;
};

#endif // KEYFRAME_H
