#ifndef SUBJECT_CONTROLLER_H
#define SUBJECT_CONTROLLER_H
#include "subject.h"

#include <vector>

class file_manager {
private:
  std::vector<subject> subjects;

public:
  file_manager();
  ~file_manager();

  void load();
  void save();

  void add_subject(const subject& new_subject);
  void remove_subject(const subject& subject);
};

#endif // SUBJECT_CONTROLLER_H
