#include "interpolator.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

Task::Task(float from, float to, float duration)
    : from(from), to(to), duration(duration) {}

Interpolator::Interpolator()
    : taskIndex(0), currentTask(nullptr), duration(0), interpolaterValue(0),
      loop(true) {}

void Interpolator::update(float dt) {

  duration += dt;

  // If there is no current task, get the first task
  if (currentTask == nullptr) {
    if (!tasks.empty()) {
      currentTask = &tasks[taskIndex];
      duration = 0;
    } else {
      TraceLog(LOG_WARNING,
               "Failed adding the first task because tasks is empty");
      return;
    }
  }

  // Check if the current task is done
  if (duration >= currentTask->duration) {
    if (++taskIndex < tasks.size()) {
      currentTask = &tasks[taskIndex];
      duration -= tasks[taskIndex - 1].duration;
    } else if (loop) {
      taskIndex = 0;
      currentTask = &tasks[taskIndex];
      duration -= tasks[tasks.size()-1].duration;
    } else {
      std::cout << "Animation finished" << std::endl;
      currentTask = nullptr;
      interpolaterValue = 0;
      return;
    }
  }

  // Update interpolator value
  interpolaterValue = Lerp(currentTask->from, currentTask->to,
                           duration / currentTask->duration);
}

void Interpolator::addTask(Task t) { tasks.push_back(t); }

float Interpolator::getValue() const { return interpolaterValue; }

void Interpolator::clearTasks() { tasks.clear(); }

void Interpolator::reset() {
  taskIndex = 0;
  currentTask = nullptr;
  duration = 0;
  interpolaterValue = 0;
  loop = true;
}
