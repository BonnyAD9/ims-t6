#pragma once

#include <optional>
#include <span>
#include <string>

#include "../config.hpp"

struct Args {
    Args(std::span<char *> args);

    Config config;
    std::optional<std::string> output;
    std::optional<long> rng_seed;
    bool help = false;
};
