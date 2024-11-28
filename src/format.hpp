#pragma once

#include <format>
#include <iostream>
#include <stdexcept>

#include <simlib.h>

#ifdef NDEBUG
#define DEBUG(...)
#else
#define DEBUG(...) std::cerr << std::format(__VA_ARGS__) << '\n';
#endif

#define PRINT(...) Print("%s", std::format(__VA_ARGS__).c_str())
#define PRINTLN(...) Print("%s\n", std::format(__VA_ARGS__).c_str())

#define THROW(...) throw std::runtime_error(std::format(__VA_ARGS__))
