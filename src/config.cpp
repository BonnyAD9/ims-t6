#include "config.hpp"

#include <format>

#include "format.hpp"

void Config::init() {
    auto ndiv = 1 / fmax_redirect();
    p_unknown_number *= ndiv;
    p_direct *= ndiv;
    p_long_distance *= ndiv;
    p_redirect *= ndiv;

    while (operators.size() < op_cnt) {
        operators.push_back(std::make_unique<Operator>(
            std::format("operator{}", operators.size())
        ));
    }
}

Operator &Config::rng_op() {
    return *operators[std::size_t(Random() * double(operators.size()))];
}

void Config::output() {
    auto avg_wait = s_wait_time / double(s_finished_calls);
    auto avg_call = s_call_time / double(s_finished_calls);
    auto avg_ring = s_ring_time / double(s_finished_calls);
    auto avg_total = avg_wait + avg_call + avg_ring;
    PRINTLN("General:");
    PRINTLN("  Started calls : {}", s_started_calls);
    PRINTLN("  Complete calls: {}", s_finished_calls);
    PRINTLN("  Avg total time: {}", avg_total);
    PRINTLN("  Avg wait time : {}", avg_wait);
    PRINTLN("  Avg ring time : {}", avg_ring);
    PRINTLN("  Avg call time : {}", avg_call);
}
