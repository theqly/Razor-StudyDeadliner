#include "subjects_controller.h"

#include <iostream>

subjects_controller::subjects_controller() : _fm("../resources/user_tasks.json") {
  _subjects = _fm.load();
  _subjects_count = _subjects.size();
}

subjects_controller::~subjects_controller() {
}

bool subjects_controller::add_subject(const std::string &name) {
  _subjects.push_back(subject(_subjects_count, name));
  ++_subjects_count;
  return true;
}

bool subjects_controller::remove_subject(const int id) {
  for (auto it = _subjects.begin(); it != _subjects.end(); ++it) {
    if (it->get_id() == id) {
      _subjects.erase(it);
      return true;
    }
  }
  return false;
}

void subjects_controller::handle_update() const {
  if(!_fm.save(_subjects)) {
    std::cerr << "Error while saving subjects data to file" << std::endl;
  }
}


std::vector<subject> subjects_controller::get_subjects() const {
  return _subjects;
}

subject &subjects_controller::get_subject_by_id(const int id) {
  for (subject& s : _subjects) {
    if(s.get_id() == id) return s;
  }
  throw std::runtime_error("Subject not found");
}


file_manager subjects_controller::get_file_manager() const { return _fm; }




