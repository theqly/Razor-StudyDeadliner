#include "task.h"

task::task() = default;

task::task(const int id) : _id(id), _name("unnamed"), _description("no description") {}

task::task(const int id, const std::string &name) : _id(id), _name(name), _description("no description") {}

task::task(const int id, std::string &&name) : _id(id), _name(name), _description("no description") {}

task::task(const int id, const std::string &name, const std::string &description)
    : _id(id), _name(name), _description(description) {}

task::task(const int id, std::string &&name, std::string &&description)
    : _id(id), _name(name), _description(description) {}

task::~task() = default;


task &task::operator=(const task &t) = default;

bool task::operator==(const task &other) const {
    return _id == other._id;
}


void task::update_readiness(const float readiness) {
    _readiness = readiness;
}
