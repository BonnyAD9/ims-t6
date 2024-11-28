#include "operator.hpp"

#include "format.hpp"

void Operator::start() { ++_started; }

void Operator::end() { ++_finished; }

void Operator::break_start() {
    _utilization += Time - _start_time;
    _start_time = Time;
}

void Operator::break_end() {
    _break_time += Time - _start_time;
    _start_time = Time;
    ++_break_cnt;
}

void Operator::use(Entity *ent, EntityPriority_t priority) {
    if (ent == _cur) {
        return;
    }

    if (!_cur) {
        _start_time = Time;
        _cur = ent;
        return;
    }
    auto p = ent->Priority;
    ent->Priority = priority;
    _queue.Insert(ent);
    ent->Priority = p;
    ent->Passivate();
}

void Operator::release(Entity *ent) {
    if (_cur != ent) {
        DEBUG("Releasing operator when not active.");
        return;
    }

    if (_queue.Empty()) {
        _cur = nullptr;
        _utilization += Time - _start_time;
        return;
    }
    _cur = _queue.GetFirst();
    _cur->Activate();
}

void Operator::output() {
    auto util = _utilization;
    if (_cur) {
        util += Time - _start_time;
    }

    PRINTLN("Operator: {}", _name);
    PRINTLN("  utilization: {}", util / (Time - StartTime));
    PRINTLN("  users      : {}", _started);
    PRINTLN("  whole calls: {}", _finished);
    PRINTLN("  break count: {}", _break_cnt);
    PRINTLN("  break_time : {}", _break_time);
}
