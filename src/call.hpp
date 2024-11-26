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

    Call(Config &config, bool incoming)
        : _config(config),
          _redirected(nullptr),
          _incoming(incoming),
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
    bool _incoming = false;
    Operator &_operator;

    double _start_time = 0;
    double _end_time = 0;
    double _ring_time = 0;
    double _call_time = 0;
};
