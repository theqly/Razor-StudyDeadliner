#ifndef SUBJECTS_CONTROLLER_H
#define SUBJECTS_CONTROLLER_H
#include <file_manager.h>

class subjects_controller {
private:
  int _subjects_count;
  int _next_id;
  file_manager _fm;
  std::vector<subject> _subjects;

public:
  subjects_controller();
  bool add_subject(const std::string &name, const std::string &description);
  bool remove_subject(int id);

  void handle_update();

  [[nodiscard]] std::vector<subject>& get_subjects();
  subject& get_subject_by_id(int id);
  float get_total_readiness();

  [[nodiscard]] file_manager get_file_manager() const;

  ~subjects_controller();
};

#endif // SUBJECTS_CONTROLLER_H
