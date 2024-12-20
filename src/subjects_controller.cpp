#include "subjects_controller.h"

#include <iostream>

subjects_controller::subjects_controller() : _next_id(0), _fm(std::string(RESOURCES_PATH) + "/user_tasks.json") {
  _subjects = _fm.load();
  _subjects_count = _subjects.size();
  for (subject& s : _subjects) {
    if(s.get_id() >= _next_id) _next_id = s.get_id() + 1;
  }
}

subjects_controller::~subjects_controller() = default;

bool subjects_controller::add_subject(const std::string &name, const std::string &description) {

  subject new_subject(_next_id, name);
  new_subject.change_description(description);
  _subjects.push_back(new_subject);
  ++_subjects_count;
  ++_next_id;
  return true;
}

bool subjects_controller::remove_subject(const int id) {
  for (auto it = _subjects.begin(); it != _subjects.end(); ++it) {
    if (it->get_id() == id) {
      _subjects.erase(it);
      --_subjects_count;
      return true;
    }
  }
  return false;
}

void subjects_controller::handle_update() {
  if(!_fm.save(_subjects)) {
    std::cerr << "Error while saving subjects data to file" << std::endl;
  }
}


std::vector<subject>& subjects_controller::get_subjects() {
  return _subjects;
}

subject &subjects_controller::get_subject_by_id(const int id) {
  for (subject& s : _subjects) {
    if(s.get_id() == id) return s;
  }
  throw std::runtime_error("Subject not found");
}

float subjects_controller::get_total_readiness() {
  float readiness = 0.0f;

  if(_subjects_count == 0) return 1.0f;

  for(const subject& s : _subjects) {
    readiness += s.get_readiness();
  }

  return readiness / static_cast<float>(_subjects_count);
}




