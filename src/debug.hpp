#pragma once

#include <format>
#include <iostream>

#define DEBUG(...) std::cerr << std::format(__VA_ARGS__) << '\n';
