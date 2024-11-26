#pragma once

#include <simlib.h>

#include "call.hpp"
#include "config.hpp"
#include "debug.hpp"

class OutgoingCall : public Event {
public:
    OutgoingCall(Config &conf) : _config(conf) { }

    void Behavior() override;

private:
    Config &_config;
};
