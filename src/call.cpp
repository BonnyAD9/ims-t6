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
    constexpr double P_KNOWN_NUMBER = 0.95;
    Release(_operator);
    Wait(Exponential(_config.long_distance_wait));
    if (Random() < P_KNOWN_NUMBER) {
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
    constexpr double F_UNKNOWN = 0.05;
    constexpr double F_DIRECT = 0.7 + F_UNKNOWN;
    constexpr double F_LONG_DISTANCE = 0.1 + F_DIRECT;

    auto rn = Random();
    if (_redirected) {
        return rn >= F_UNKNOWN ? Action::DIRECTLY : Action::UNKNOWN_NUMBER;
    }
    if (rn < F_UNKNOWN) {
        return Action::UNKNOWN_NUMBER;
    }
    if (rn < F_DIRECT) {
        return Action::DIRECTLY;
    }
    if (rn < F_LONG_DISTANCE) {
        return Action::LONG_DISTANCE;
    }
    return Action::REDIRECT;
}
