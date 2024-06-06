#include <vector>

class Task {
public:
  Task(float, float, float);
  float from;
  float to;
  float duration;
};

class Interpolator {
public:
  Interpolator();
  void update(float dt);
  float getValue() const;
  void reset();
  void addTask(Task);
  void clearTasks();
  std::vector<Task> tasks;


private:
  size_t taskIndex;
  Task *currentTask;
  float duration;
  float interpolaterValue;
  bool loop;
};
