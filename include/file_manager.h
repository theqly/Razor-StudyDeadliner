#ifndef SUBJECT_CONTROLLER_H
#define SUBJECT_CONTROLLER_H
#include "subject.h"
#include <nlohmann/json.hpp>
#include <vector>

class file_manager {
private:

  const std::string _file_path;

  static nlohmann::json subject_to_json(const subject &subj);
  static nlohmann::json task_to_json(const task &t);
  static subject json_to_subject(const nlohmann::json &subjJson);
  static task json_to_task(const nlohmann::json &taskJson);
public:
  file_manager(const std::string &file_path);
  bool save(const std::vector<subject> &subjects) const;
  std::vector<subject> load() const;

};

#endif // SUBJECT_CONTROLLER_H
