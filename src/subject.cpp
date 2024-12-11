#include "subject.h"

#include <stdexcept>

subject::subject(const int id)
    : _id(id), _tasks_count(0), _name("unnamed"), _tasks(_tasks_count) {}

subject::subject(const int id, const std::string &name)
    : _id(id), _tasks_count(0), _name(name), _tasks(_tasks_count) {}

subject::subject(const int id, std::string &&name)
    : _id(id), _tasks_count(0), _name(name), _tasks(_tasks_count) {}

subject::~subject() = default;

bool subject::add_task(const task &new_task) {
  for( task &t : _tasks ) {
    if( new_task.get_id() == t.get_id()) return false;
  }
  _tasks.push_back(new_task);
  ++_tasks_count;
  return true;
}


bool subject::add_task(const std::string& name, const std::string& description, const std::string& deadline) {
  task new_task(_tasks_count, name, description);
  new_task.change_deadline(deadline);
  _tasks.push_back(new_task);

  return true;
}

bool subject::remove_task(const int id) {
  for (auto it = _tasks.begin(); it != _tasks.end(); ++it) {
    if(it->get_id() == id) {
      _tasks.erase(it);
      return true;
    }
  }
  return false;
}

bool subject::change_name(const std::string &name) {
  if (name.empty())
    return false;
  _name = name;
  return true;
}

float subject::get_readiness() const {
  float readiness = 0.0f;

  if(_tasks_count == 0) return readiness;

  for(const task& t : _tasks) {
    readiness += t.get_readiness();
  }

  return readiness / _tasks_count;
}

std::vector<task> subject::get_tasks() const { return _tasks; }

std::string subject::get_name() const { return _name; }

int subject::get_id() const { return _id; }

task& subject::get_task_by_id(const int id) {
  for (auto &t : _tasks) {
    if (t.get_id() == id) {
      return t;
    }
  }
  throw std::runtime_error("Task with the specified ID not found");
}

