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

    void start();
    void end();

    void break_start();
    void break_end();

    void use(Entity *ent, EntityPriority_t priority);
    void release(Entity *ent);
    void output();

    enum {
        ENTER_PRIORITY = 1,
        REDIRECT_PRIORITY,
        END_PRIORITY,
        BREAK_PRIORITY,
    };

private:
    std::string _name;
    Entity *_cur = nullptr;
    Queue _queue;

    double _utilization = 0;
    double _start_time = 0;
    std::size_t _started;
    std::size_t _finished;
    std::size_t _break_cnt = 0;
    double _break_time = 0;
};
