#ifndef TASK_H
#define TASK_H

#include <string>

class task {
private:
  const std::string _name;
  const std::string _description;

  float _readiness = 0.0;
  bool _is_done = false;
  //TODO: deadline
public:
  task();
  explicit task(const std::string &name);
  explicit task(std::string &&name);
  task(const std::string &name, const std::string &description);
  task(std::string &&name, std::string &&description);

  void update_readiness(float readiness);

  ~task();
};

#endif //TASK_H
