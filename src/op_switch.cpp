#include "op_switch.hpp"

#include "format.hpp"

void OpSwitch::Behavior() {
    _operator.use(this, Operator::BREAK_PRIORITY);
    _operator.break_start();
    Wait(Exponential(_config.switch_time));
    _operator.break_end();
    _operator.release(this);
}
