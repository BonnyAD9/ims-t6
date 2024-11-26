#include "outgoing_call.hpp"

void OutgoingCall::Behavior() {
    (new Call(_config))->Activate();
    Activate(Time + Exponential(_config.call_distance));
}
