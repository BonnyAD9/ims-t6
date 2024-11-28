#include "op_break.hpp"

#include "format.hpp"
#include "op_switch.hpp"

void OpBreak::Behavior() {
    auto fut = Time + Uniform(_config.min_duty, _config.max_duty);
    (new OpSwitch(_config, _operator))->Activate(fut);
    Activate(fut);
}
