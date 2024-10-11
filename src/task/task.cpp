#include "task/task.h"

task::task() : _name("unnamed"), _description("no description") {}

task::task(const std::string &name) : _name(name), _description("no description") {}

task::task(std::string &&name) : _name(name), _description("no description") {}

task::task(const std::string &name, const std::string &description)
    : _name(name), _description(description) {}

task::task(std::string &&name, std::string &&description)
    : _name(name), _description(description) {}

void task::update_readiness(const float readiness) {
    _readiness = readiness;
}
