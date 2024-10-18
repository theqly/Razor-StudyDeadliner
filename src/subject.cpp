#include "subject.h"

subject::subject(const int id) : _id(id), _name("unnamed"), _tasks(2) {}

subject::subject(const int id, const std::string &name) : _id(id), _name(name), _tasks(2) {}

subject::subject(const int id, std::string &&name) : _id(id), _name(name), _tasks(2) {}

void subject::add_task(const task &new_task) {
  _tasks.push_back(new_task);
}

void subject::remove_task(const task &new_task) {
  //TODO
}

 subject::~subject() = default;



