#pragma once

#include <simlib.h>

#include "config.hpp"

class OpBreak : public Event {
public:
    OpBreak(Config &config, Operator &op) : _config(config), _operator(op) { }

    void Behavior() override;

private:
    Config &_config;
    Operator &_operator;
};
