#pragma once

#include <simlib.h>

#include "config.hpp"

class OpSwitch : public Process {
public:
    OpSwitch(Config &conf, Operator &op) : _config(conf), _operator(op) { }

    void Behavior() override;

private:
    Config &_config;
    Operator &_operator;
};
