#pragma once

#include <format>
#include <iostream>
#include <simlib.h>

#define DEBUG(...) std::cerr << std::format(__VA_ARGS__) << '\n';

#define PRINT(...) Print("%s", std::format(__VA_ARGS__).c_str())
#define PRINTLN(...) Print("%s\n", std::format(__VA_ARGS__).c_str())
