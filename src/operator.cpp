#include "operator.hpp"

#include "debug.hpp"

void Operator::use(Entity *ent, EntityPriority_t priority) {
    if (!_cur) {
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
        return;
    }
    _cur = _queue.GetFirst();
    _cur->Activate();
}
