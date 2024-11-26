#pragma once

#include <map>
#include <string>
#include <vector>

#include <simlib.h>

class Operator {
public:
    Operator(std::string name)
        : _name(std::move(name)), _queue(_name.c_str()) { }

    void use(Entity *ent, EntityPriority_t priority);
    void release(Entity *ent);

private:
    std::string _name;
    Entity *_cur = nullptr;
    Queue _queue;
};
