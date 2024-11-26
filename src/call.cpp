#include "call.hpp"

#include <algorithm>

#include "debug.hpp"

void Call::Behavior() {
    ++_config.s_started_calls;
    _start_time = Time;
    _operator.start();
    _operator.use(
        this,
        _redirected || _incoming ? Operator::REDIRECT_PRIORITY
                                 : Operator::ENTER_PRIORITY
    );
    Wait(Uniform(_config.ask_number_time_min, _config.ask_number_time_max));
    auto action = get_action();
    switch (action) {
    case Action::UNKNOWN_NUMBER:
        end();
        break;
    case Action::DIRECTLY:
        _operator.release(this);
        direct_call();
        break;
    case Action::LONG_DISTANCE:
        _operator.release(this);
        long_distance_call();
        break;
    case Action::REDIRECT:
        _operator.release(this);
        redirect_call();
        break;
    }
}

void Call::direct_call() {
    auto ring = Normal(_config.pick_time, _config.pick_deviation);
    _ring_time += std::clamp(ring, 0., _config.ring_timeout);
    if (ring <= 0) { // User is already calling
        end();
        return;
    }
    if (ring > _config.ring_timeout) {
        // Ringing is intercepted because the called user is not picking
        Wait(_config.ring_timeout);
        end();
        return;
    }
    Wait(ring);
    call();
}

void Call::long_distance_call() {
    Wait(Exponential(_config.long_distance_wait));
    if (Random() >= _config.p_unknown_number) {
        direct_call();
        return;
    }
    end();
}

void Call::redirect_call() {
    (new Call(_config, this))->Activate();
    Passivate();
    end();
}

void Call::call() {
    _call_time = Exponential(_config.call_time);
    Wait(_call_time);
    end();
}

void Call::end() {
    _operator.use(this, Operator::END_PRIORITY);
    Wait(_config.end_time);
    _operator.end();
    _end_time = Time;
    collect();
    _operator.release(this);
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

void Call::collect() {
    auto total = _end_time - _start_time;
    auto wait_time = total - _ring_time - _call_time;
    _config.s_wait_time += wait_time;
    _config.s_call_time += _call_time;
    _config.s_ring_time += _ring_time;
    ++_config.s_finished_calls;
    // PRINTLN(
    //     "Call: {} {}",
    //     _redirected ? "redirected" : "",
    //     _incoming ? "incoming" : ""
    // );
    // PRINTLN("  Total time: {}", total);
    // PRINTLN("  Wait time : {}", wait_time);
    // PRINTLN("  Call time : {}", _call_time);
    // PRINTLN("  Ring time : {}", _ring_time);
}
