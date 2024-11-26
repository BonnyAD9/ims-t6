#pragma once

#include "config.hpp"

enum class Action {
    UNKNOWN_NUMBER,
    DIRECTLY,
    LONG_DISTANCE,
    REDIRECT,
};

class Call : public Process {
public:
    Call(Config &config, Call *redirected = nullptr)
        : _config(config),
          _redirected(redirected),
          _operator(config.rng_op()) { }

    void Behavior() override;

private:
    void direct_call();
    void long_distance_call();
    void redirect_call();
    void call();
    void end();
    Action get_action();

    Config &_config;
    Call *_redirected;
    Operator &_operator;
};
