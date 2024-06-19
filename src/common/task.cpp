#include "task.h"
#include <raylib.h>
#include <raymath.h>

size_t GroupTag = 0;
size_t SeqTag = 0;
size_t MoveVec2Tag = 0;

VTable taskVTable;

bool updateTask(Task task, Env env) {
  return taskVTable.getFuncs(task.taskID).update(env, task.getData());
}
void resetTask(Task task, Env env) {
  taskVTable.getFuncs(task.taskID).reset(env, task.getData());
}

size_t VTable::append(TaskFuncs f) {
  funcs.push_back(f);
  return funcs.size() - 1;
}

void VTable::rebuild() {
  funcs.clear();
  // update all tags with indexes of Vtable
  GroupTag = append({.update = TaskGroup::update, .reset = TaskGroup::reset});
  SeqTag = append({.update = TaskSeq::update, .reset = TaskSeq::reset});
  MoveVec2Tag =
      append({.update = TaskMoveVec2::update, .reset = TaskMoveVec2::reset});
}

TaskFuncs VTable::getFuncs(size_t id) { return funcs[id]; }

// TASK IMPLEMENTATIONS
// TASK Group
bool TaskGroup::update(Env env, void *rawData) {
  GroupData *data = static_cast<GroupData *>(rawData);
  bool finished = true;
  for (auto task : data->tasks) {
    if (!updateTask(task, env)) {
      finished = false;
    }
  }
  return finished;
}

void TaskGroup::reset(Env env, void *rawData) {
  GroupData *data = static_cast<GroupData *>(rawData);
  for (auto task : data->tasks) {
    resetTask(task, env);
  }
}

// TASK Sequence

bool TaskSeq::update(Env env, void *rawData) {
  SeqData *data = static_cast<SeqData *>(rawData);
  if (data->currentTask >= data->tasks.size()) {
    return true;
  }

  if (updateTask(data->tasks[data->currentTask], env)) {
    data->currentTask++;
  }

  if (data->currentTask >= data->tasks.size()) {
    return true;
  } else {
    return false;
  }
}

void TaskSeq::reset(Env env, void *rawData) {
  SeqData *data = static_cast<SeqData *>(rawData);
  for (int i = 0; i < data->tasks.size(); i++) {
    resetTask(data->tasks[i], env);
  }
  data->currentTask = 0;
}

// TASK MoveVec2
Task TaskMoveVec2::create(Vector2 *val, Vector2 moveTo, float duration) {
  auto *data = new MoveVec2Data();
  data->value = val;
  data->moveTo = moveTo;
  data->duration = duration;
  data->started = false;
  data->t = 0;
  return Task(MoveVec2Tag, data);
}

bool TaskMoveVec2::update(Env env, void *rawData) {
  MoveVec2Data *data = static_cast<MoveVec2Data *>(rawData);
  if (data == nullptr) {
    TraceLog(LOG_ERROR, "MoveVec2Data is null in update");
    return true;
  }

  if (data->t >= 1.0) {
    return true;
  }

  if (!data->started) {
    data->startPos = *data->value;
    data->started = true;
  }

  data->t = ((data->t * data->duration) + env.getDeltaT()) / data->duration;
  Vector2 moveDistance = Vector2Subtract(data->moveTo, data->startPos);
  *data->value = Vector2Lerp(data->startPos, data->moveTo, data->t);

  return data->t >= 1.0;
}

void TaskMoveVec2::reset(Env env, void *rawData) {
  MoveVec2Data *data = static_cast<MoveVec2Data *>(rawData);
  data->t = 0;
  data->value->x = data->startPos.x;
  data->value->y = data->startPos.y;
  data->started = false;
}
