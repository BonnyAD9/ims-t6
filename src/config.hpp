#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <simlib.h>

#include "operator.hpp"

struct Config {
    // NOLINTBEGIN(readability-magic-numbers)

    double run_time = 1000;

    std::vector<std::unique_ptr<Operator>> operators;
    std::size_t op_cnt = 3;

    double ask_number_time_min = 20;
    double ask_number_time_max = 60;

    double pick_time = 60;
    double pick_deviation = 30;

    double call_time = 5 * 60;
    double long_distance_wait = 20 * 60;
    double end_time = 5;
    double ring_timeout = 120;

    double p_unknown_number = 0.05;
    double p_direct = 0.7;
    double p_long_distance = 0.1;
    double p_redirect = 0.15;

    double call_distance = 60;

    // NOLINTEND(readability-magic-numbers)

    [[nodiscard]]
    constexpr double f0_unknown_number() const {
        return p_unknown_number;
    }

    [[nodiscard]]
    constexpr double f1_direct() const {
        return p_direct + f0_unknown_number();
    }

    [[nodiscard]]
    constexpr double f2_long_distance() const {
        return p_long_distance + f1_direct();
    }

    [[nodiscard]]
    constexpr double fmax_redirect() const {
        return p_redirect + f2_long_distance();
    }

    void init();
    Operator &rng_op();
};
