#ifndef SUBJECT_H
#define SUBJECT_H
#include "task/task.h"

#include <string>
#include <vector>

class subject {
private:

  const std::string _name;
  std::vector<task> _tasks;
  float _readiness = 0;

public:
  subject();
  explicit subject(const std::string &name);
  explicit subject(std::string &&name);

  void add_task(const task &task);
  void remove_task(const task &task);

  ~subject();
};

#endif //SUBJECT_H
