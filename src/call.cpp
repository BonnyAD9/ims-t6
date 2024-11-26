#include "call.hpp"

void Call::Behavior() {
    Seize(_operator, _redirected ? REDIRECT_PRIORITY : ENTER_PRIORITY);
    Wait(Uniform(_config.ask_number_time_min, _config.ask_number_time_max));
    auto action = get_action();
    switch (action) {
    case Action::UNKNOWN_NUMBER:
        end();
        break;
    case Action::DIRECTLY:
        direct_call();
        break;
    case Action::LONG_DISTANCE:
        long_distance_call();
        break;
    case Action::REDIRECT:
        redirect_call();
        break;
    }
}

void Call::direct_call() {
    auto wait = Normal(_config.pick_time, _config.pick_deviation);
    if (wait <= 0) { // User is already calling
        end();
        return;
    }
    Release(_operator);
    if (wait > _config.ring_timeout) {
        // Ringing is intercepted because the called user is not picking
        Wait(_config.ring_timeout);
        end();
        return;
    }
    Wait(wait);
    call();
}

void Call::long_distance_call() {
    Release(_operator);
    Wait(Exponential(_config.long_distance_wait));
    if (Random() >= _config.p_unknown_number) {
        Wait(Exponential(_config.call_time));
    }
    end();
}

void Call::redirect_call() {
    Release(_operator);
    (new Call(_config, this))->Activate();
    Passivate();
    end();
}

void Call::call() {
    Wait(Exponential(_config.call_time));
    end();
}

void Call::end() {
    Seize(_operator, END_PRIORITY);
    Wait(_config.end_time);
    Release(_operator);
    if (_redirected) {
        _redirected->Activate();
    }
    Terminate();
}

Action Call::get_action() {
    auto rn = Random();
    if (_redirected) {
        return rn >= _config.p_unknown_number ? Action::DIRECTLY
                                              : Action::UNKNOWN_NUMBER;
    }
    if (rn < _config.f0_unknown_number()) {
        return Action::UNKNOWN_NUMBER;
    }
    if (rn < _config.f1_direct()) {
        return Action::DIRECTLY;
    }
    if (rn < _config.f2_long_distance()) {
        return Action::LONG_DISTANCE;
    }
    return Action::REDIRECT;
}
