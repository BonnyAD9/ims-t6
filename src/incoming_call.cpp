#include "incoming_call.hpp"

void IncomingCall::Behavior() {
    (new Call(_config, true))->Activate();
    Activate(Time + Exponential(_config.incall_distance));
}
