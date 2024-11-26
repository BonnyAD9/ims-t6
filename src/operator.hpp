#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <simlib.h>

class Operator {
public:
    Operator(std::string name)
        : _name(std::move(name)), _queue(_name.c_str()) { }

    void new_call(Entity *call, bool redirected);
    void end(Entity *ent);

    void use(Entity *ent, EntityPriority_t priority);
    void release(Entity *ent);
    void output();

    enum {
        ENTER_PRIORITY = 1,
        REDIRECT_PRIORITY,
        END_PRIORITY,
    };

private:
    std::string _name;
    Entity *_cur = nullptr;
    Queue _queue;

    double _utilization = 0;
    double _start_time = 0;
    std::unordered_set<std::intptr_t> _seen;
    std::unordered_set<std::intptr_t> _finished;
};
