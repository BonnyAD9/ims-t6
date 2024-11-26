#pragma once

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

#include <simlib.h>

class Operator {
public:
    Operator(std::string name)
        : _name(std::move(name)), _queue(_name.c_str()) { }

    void use(Entity *ent, EntityPriority_t priority);
    void release(Entity *ent);
    void output();

private:
    std::string _name;
    Entity *_cur = nullptr;
    Queue _queue;

    double _utilization = 0;
    double _start_time = 0;
    std::unordered_set<std::intptr_t> _users;
};
