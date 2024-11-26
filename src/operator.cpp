#include "operator.hpp"

#include "debug.hpp"

void Operator::use(Entity *ent, EntityPriority_t priority) {
    _users.insert(reinterpret_cast<intptr_t>(ent));
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
    PRINTLN("Operator: {}", _name);
    PRINTLN("  utilization: {}", _utilization / Time);
    PRINTLN("  users      : {}", _users.size());
}
