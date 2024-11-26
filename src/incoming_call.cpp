#include "incoming_call.hpp"

void IncomingCall::Behavior() {
    DEBUG("Generating ingoing: {}", Time);
    (new Call(_config, true))->Activate();
    Activate(Time + Exponential(_config.incall_distance));
}
