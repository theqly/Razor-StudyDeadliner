#include "subject.h"

#include <stdexcept>

subject::subject(const int id)
    : _id(id), _tasks_count(0), _next_id(0),_name("unnamed"), _tasks(_tasks_count) {}

subject::subject(const int id, const std::string &name)
    : _id(id), _tasks_count(0), _next_id(0), _name(name), _tasks(_tasks_count) {}

subject::subject(const int id, std::string &&name)
    : _id(id), _tasks_count(0), _next_id(0), _name(name), _tasks(_tasks_count) {}

subject::~subject() = default;

bool subject::add_task(const std::string &name, const std::string &description,
                       const std::string &deadline) {
  task new_task(_next_id, name);
  new_task.change_description(description);
  new_task.change_deadline(deadline);
  _tasks.push_back(new_task);
  ++_next_id;
  ++_tasks_count;
  return true;
}

bool subject::add_task(const int id, const std::string &name, const std::string &description,
                       const std::string &deadline) {
  if(id >= _next_id) _next_id = id + 1;
  task new_task(id, name);
  new_task.change_description(description);
  new_task.change_deadline(deadline);
  _tasks.push_back(new_task);
  ++_tasks_count;
  return true;
}


bool subject::remove_task(const int id) {
  for (auto it = _tasks.begin(); it != _tasks.end(); ++it) {
    if(it->get_id() == id) {
      _tasks.erase(it);
      --_tasks_count;
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

bool subject::change_description(const std::string &description) {
  if (description.empty())
    return false;
  _description = description;
  return true;
}


float subject::get_readiness() const {
  float readiness = 0.0f;

  if(_tasks_count == 0) return 1.0f;

  for(const task& t : _tasks) {
    readiness += t.get_readiness();
  }

  return readiness / static_cast<float>(_tasks_count);
}

std::vector<task>& subject::get_tasks() { return _tasks; }

std::string subject::get_name() const { return _name; }

std::string subject::get_description() const { return _description; }


int subject::get_id() const { return _id; }

task& subject::get_task_by_id(const int id) {
  for (auto &t : _tasks) {
    if (t.get_id() == id) {
      return t;
    }
  }
  throw std::runtime_error("Task with the specified ID not found");
}

