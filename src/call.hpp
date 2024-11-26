#pragma once

#include "config.hpp"

enum class Action {
    UNKNOWN_NUMBER,
    DIRECTLY,
    LONG_DISTANCE,
    REDIRECT,
};

enum {
    ENTER_PRIORITY = 1,
    REDIRECT_PRIORITY,
    END_PRIORITY,
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
    Facility &_operator;
};
