#include "file_manager.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

 file_manager::file_manager(const std::string &file_path) : _file_path(file_path){ }


std::vector<subject> file_manager::load() const {
  std::vector<subject> subjects;

  std::ifstream file(_file_path);
  if (!file.is_open()) {
    return subjects;
  }

  json jsonData;
  file >> jsonData;
  file.close();

  for (const auto &subjJson : jsonData) {
    subjects.push_back(json_to_subject(subjJson));
  }

  return subjects;
}

bool file_manager::save(const std::vector<subject> &subjects) const {
  json jsonData;
  for (const auto &subj : subjects) {
    jsonData.push_back(subject_to_json(subj));
  }

  std::ofstream file(_file_path);
  if (!file.is_open()) {
    return false;
  }

  file << jsonData.dump(4);
  file.close();

  return true;
}

nlohmann::json file_manager::subject_to_json(const subject &subj) {
  json subjJson;
  subjJson["id"] = subj.get_id();
  subjJson["name"] = subj.get_name();
  subjJson["readiness"] = subj.get_readiness();

  std::vector<json> tasksJson;
  for (const auto &t : subj.get_tasks()) {
    tasksJson.push_back(task_to_json(t));
  }

  subjJson["tasks"] = tasksJson;
  return subjJson;
}

nlohmann::json file_manager::task_to_json(const task &t) {
  json taskJson;
  taskJson["id"] = t.get_id();
  taskJson["name"] = t.get_name();
  taskJson["description"] = t.get_description();
  taskJson["deadline"] = t.get_deadline();
  taskJson["readiness"] = t.get_readiness();
  return taskJson;
}

subject file_manager::json_to_subject(const nlohmann::json &subjJson) {
  subject subj(subjJson.at("id").get<int>(), subjJson.at("name").get<std::string>());

  for (const auto &taskJson : subjJson.at("tasks")) {
    subj.add_task(json_to_task(taskJson));
  }

  return subj;
}

task file_manager::json_to_task(const nlohmann::json &taskJson) {
  task t(taskJson.at("id").get<int>(), taskJson.at("name").get<std::string>());
  t.change_description(taskJson.at("description").get<std::string>());
  t.change_deadline(taskJson.at("deadline").get<std::string>());
  t.change_readiness(taskJson.at("readiness").get<float>());
  return t;
}






