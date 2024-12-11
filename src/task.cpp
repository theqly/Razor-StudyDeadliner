#include "task.h"

task::task() = default;

task::task(const int id) : _id(id), _name("unnamed"), _description("no description"), _deadline("no deadline") {}

task::task(const int id, const std::string &name) : _id(id), _name(name), _description("no description"), _deadline("no deadline") {}

task::task(const int id, std::string &&name) : _id(id), _name(name), _description("no description"), _deadline("no deadline") {}

task::~task() = default;

task &task::operator=(const task &t) = default;

bool task::operator==(const task &other) const {
    return _id == other._id;
}

bool task::change_name(const std::string &name) {
    if(name.empty()) return false;
    _name = name;
    return true;
}

bool task::change_description(const std::string &description) {
    if(description.empty()) return false;
    _description = description;
    return true;
}

bool task::change_deadline(const std::string& deadline) {
    _deadline = deadline;
    return true;
}


bool task::change_readiness(const float readiness) {
    if(readiness < 0.0f || readiness > 1.0f) return false;
    _readiness = readiness;
    return true;
}

int task::get_id() const { return _id; }
std::string task::get_name() const { return _name; }
std::string task::get_description() const { return _description; }
std::string task::get_deadline() const { return _deadline; }
float task::get_readiness() const { return _readiness; }



