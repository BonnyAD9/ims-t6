#include "config.hpp"

#include <format>

void Config::init() {
    auto ndiv = 1 / fmax_redirect();
    p_unknown_number *= ndiv;
    p_direct *= ndiv;
    p_long_distance *= ndiv;
    p_redirect *= ndiv;

    while (operators.size() < op_cnt) {
        auto s = std::format("operator{}", operators.size());
        s.reserve(sizeof(std::string));
        op_names.push_back(std::move(s));
        operators.push_back(
            std::make_unique<Facility>(op_names.rbegin()->c_str())
        );
    }
}

Facility &Config::rng_op() {
    return *operators[std::size_t(Random() * double(operators.size()))];
}
