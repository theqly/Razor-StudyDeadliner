#ifndef SUBJECT_H
#define SUBJECT_H
#include "task.h"

#include <string>
#include <vector>

class subject {
private:
  int _id;
  int _tasks_count;
  std::string _name;
  std::vector<task> _tasks;
  float _readiness = 0.0f;

public:
  explicit subject(int id);
  subject(int id, const std::string &name);
  subject(int id, std::string &&name);

  bool add_task(const task &t);
  bool add_task(const std::string& name, const std::string& description, const std::string& deadline);
  bool remove_task(int id);

  bool change_name(const std::string &name);
  bool change_readiness(float readiness);

  [[nodiscard]] float get_readiness() const;
  [[nodiscard]] std::vector<task> get_tasks() const;
  [[nodiscard]] std::string get_name() const;
  [[nodiscard]] int get_id() const;

  [[nodiscard]] task& get_task_by_id(int id);

  ~subject();
};

#endif //SUBJECT_H
