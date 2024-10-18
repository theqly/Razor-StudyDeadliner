#ifndef TASK_H
#define TASK_H

#include <string>

class task {
private:

  int _id;

  std::string _name;
  std::string _description;

  float _readiness = 0.0;
  bool _is_done = false;
  //TODO: deadline
public:
  task();
  explicit task(int id);
  task(int id, const std::string &name);
  task(int id, std::string &&name);
  task(int id, const std::string &name, const std::string &description);
  task(int id, std::string &&name, std::string &&description);

  task& operator=(const task &t);
  bool operator==(const task &other) const;

  void update_readiness(float readiness);

  ~task();
};

#endif //TASK_H
