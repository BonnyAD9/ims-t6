#include "args.hpp"

#include <charconv>
#include <string>

#include "../format.hpp"

template<std::input_iterator I>
auto next_arg(I &it, const I &end) -> decltype(*it);
template<typename T, std::input_iterator I, typename V>
T parse_next(I &it, const I &end, V val);
template<typename T, std::input_iterator I> T parse_next(I &it, const I &end);
template<typename T> T parse(std::string_view s);

struct Positive {
    template<typename T> T operator()(T v);
};

constexpr Positive POSITIVE;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
Args::Args(std::span<char *> args) {
    using std::string_literals::operator""s;

    args = args.subspan(1);
    auto end = args.end();

    for (auto arg = args.begin(); arg != end; ++arg) {
        if (*arg == "-h"s || *arg == "-?"s || *arg == "--help"s) {
            help = true;
        } else if (*arg == "-t"s || *arg == "--time"s) {
            config.run_time = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "-o"s || *arg == "--output"s) {
            output = next_arg(arg, end);
        } else if (*arg == "--rng"s || *arg == "--rng-seed"s) {
            rng_seed = parse_next<long>(arg, end);
        } else if (*arg == "--operators"s) {
            config.op_cnt = parse_next<std::size_t>(arg, end, POSITIVE);
        } else if (*arg == "--ask-min"s) {
            config.ask_number_time_min =
                parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--ask-max"s) {
            config.ask_number_time_max =
                parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--op-ask-min"s) {
            config.op_ask_number_time_min =
                parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--op-ask-max"s) {
            config.op_ask_number_time_max =
                parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--pick-time"s) {
            config.pick_time = parse_next<double>(arg, end);
        } else if (*arg == "--pick-deviation"s) {
            config.pick_deviation = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--call-time"s) {
            config.call_time = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--long-distance-overhead"s) {
            config.long_distance_wait = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--end-overhead"s) {
            config.end_time = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--ring-timeout"s) {
            config.ring_timeout = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--p-unknown-number"s) {
            config.p_unknown_number = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--p-direct"s) {
            config.p_direct = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--p-long-distance"s) {
            config.p_long_distance = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--p-redirect"s) {
            config.p_redirect = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--out-dst"s) {
            config.call_distance = parse_next<double>(arg, end, POSITIVE);
        } else if (*arg == "--in_dst"s) {
            config.incall_distance = parse_next<double>(arg, end, POSITIVE);
        } else {
            THROW("Unknown argument `{}`", *arg);
        }
    }
}

template<std::input_iterator I>
auto next_arg(I &it, const I &end) -> decltype(*it) {
    auto &v = *it;
    if (++it == end) {
        THROW("Expected next argument after `{}`", v);
    }
    return *it;
}

template<typename T, std::input_iterator I, typename V>
T parse_next(I &it, const I &end, V val) {
    auto &v = *it;
    auto s = next_arg(it, end);
    try {
        return val(parse<T>(s));
    } catch (std::exception &ex) {
        THROW("Invalid value to `{}`: {}", v, ex.what());
    }
}

template<typename T, std::input_iterator I> T parse_next(I &it, const I &end) {
    return parse_next<T>(it, end, std::identity());
}

template<typename T> T parse(std::string_view s) {
    double res;
    auto r = std::from_chars(s.begin(), s.end(), res);
    if (r.ptr != s.end()) {
        THROW("Failed to parse `{}` to `{}`", s, typeid(double).name());
    }
    return res;
}

template<typename T> T Positive::operator()(T v) {
    if (v <= 0) {
        THROW("Value must be positive");
    }
    return v;
}
