#include "subject/subject.h"

subject::subject() : _name("unnamed"), _tasks(2) {}

subject::subject(const std::string &name) : _name(name), _tasks(2) {}

subject::subject(std::string &&name) : _name(name), _tasks(2) {}

void subject::add_task(const task &task) {
  _tasks.push_back(task);
}

void subject::remove_task(const task &task) {
  std::erase(_tasks, task);
}


