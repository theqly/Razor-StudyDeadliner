#ifndef SUBJECT_H
#define SUBJECT_H
#include "task.h"

#include <string>
#include <vector>

class subject {
private:

  int _id;

  std::string _name;
  std::vector<task> _tasks;
  float _readiness = 0;

public:
  explicit subject(int id);
  subject(int id, const std::string &name);
  subject(int id, std::string &&name);

  void add_task(const task &new_task);
  void remove_task(const task &new_task);

  ~subject();
};

#endif //SUBJECT_H
