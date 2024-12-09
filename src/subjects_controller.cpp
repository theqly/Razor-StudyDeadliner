#include "subjects_controller.h"

subjects_controller::subjects_controller() : _subjects_count(0), _fm("/home/theqly/programming/projects/nsu/ooad/"
                         "Razor-StudyDeadliner/resources/user_tasks.json") {
  _subjects = _fm.load();
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

std::vector<subject> subjects_controller::get_subjects() const {
  return _subjects;
}

file_manager subjects_controller::get_file_manager() const { return _fm; }




