#ifndef TASK_H
#define TASK_H

#include <string>

class task {
private:

  int _id{};

  std::string _name;
  std::string _description;
  std::string _deadline;
  float _readiness = 0.0;

public:
  task();
  explicit task(int id);
  task(int id, const std::string &name);
  task(int id, std::string &&name);

  task& operator=(const task &t);
  bool operator==(const task &other) const;

  bool change_name(const std::string &name);
  bool change_description(const std::string &description);
  bool change_deadline(const std::string& deadline);
  bool change_readiness(float readiness);

  [[nodiscard]] int get_id() const;
  [[nodiscard]] std::string get_name() const;
  [[nodiscard]] std::string get_description() const;
  [[nodiscard]] std::string get_deadline() const;
  [[nodiscard]] float get_readiness() const;

  ~task();
};

#endif //TASK_H
