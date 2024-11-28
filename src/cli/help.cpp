#include "help.hpp"

#include <iostream>
#include <limits>

#include "ansi_term.hpp"

#define XSTIGL00                                                               \
    RGB(250, 50, 170)                                                          \
    "x" RGB(240, 50, 180) "s" RGB(230, 50, 190) "t" RGB(220, 50, 200) "i" RGB( \
        210, 50, 210                                                           \
    ) "g" RGB(200, 50, 220) "l" RGB(190, 50, 230) "0" RGB(180, 50, 240) "0"

#define XSLEZA26                                                               \
    RGB(0, 220, 255)                                                           \
    "x" RGB(25, 200, 255) "s" RGB(50, 180, 255) "l" RGB(75, 160, 255) "e" RGB( \
        100, 140, 255                                                          \
    ) "z" RGB(125, 120, 255) "a" RGB(150, 100, 255) "2" RGB(175, 80, 255) "6"

void help() {
    std::cout
        << "Welcome in " ITALIC GREEN "ims-t6" RESET " help by " XSLEZA26 RESET
           " and " XSTIGL00 RESET "\n"
           "Version 1.0.0\n"
           "\n" GREEN "Usage:\n"
           "  " CYAN "ims-t6 " DGRAY "[" DYELLOW "flags" DGRAY "]\n"
           "\n" GREEN "Flags:\n"
           "  " YELLOW "-h  -?  --help " RESET "\n"
           "    Show this help.\n"
           "\n"
           "  " YELLOW "-t  --time " WHITE "<time>" RESET "\n"
           "    Set for how long the simulation will run. Default is 86400\n"
           "\n"
           "  " YELLOW "-o  --output " WHITE "<file>" RESET "\n"
           "    Set the output for the simulation results. This is stdout by "
           "default.\n"
           "\n"
           "  " YELLOW "--rng  --rng-seed " WHITE "<seed>" RESET "\n"
           "    Set seed for the rng. By default it is based on current "
           "time.\n"
           "\n"
           "  " YELLOW "--operators " WHITE "<count>" RESET "\n"
           "    Set the number of operators in the phone exchange. Default is "
           "3.\n"
           "\n"
           "  " YELLOW "--ask-min " WHITE "<uniform-min>" RESET "\n"
           "    Set the minimum time it takes the operator to get the calee "
           "number\n"
           "    from customer. Default is 20.\n"
           "\n"
           "  " YELLOW "--ask-max " WHITE "<uniform-max>" RESET "\n"
           "    Set the maximum time it takes the operator to get the calee "
           "number\n"
           "    from customer. Default is 60.\n"
           "\n"
           "  " YELLOW "--op-ask-min " WHITE "<uniform-min>" RESET "\n"
           "    Set the minimum time it takes the operator to get the calee "
           "number\n"
           "    from another operator. Default is 10.\n"
           "\n"
           "  " YELLOW "--op-ask-max " WHITE "<uniform-max>" RESET "\n"
           "    Set the maximum time it takes the operator to get the calee "
           "number\n"
           "    from another operator. Default is 20.\n"
           "\n"
           "  " YELLOW "--pick-time " WHITE "<normal-center>" RESET "\n"
           "    Set the time it takes calee to pick the phone. Default is "
           "60.\n"
           "\n"
           "  " YELLOW "--pick-deviation " WHITE "<normal-deviation>" RESET
           "\n"
           "    Set the deviation from the average time it takes the calee to "
           "pick\n"
           "    the phone. Default is 30.\n"
           "\n"
           "  " YELLOW "--call-time " WHITE "<exp>" RESET "\n"
           "    Set the length of call. Default is 300.\n"
           "\n"
           "  " YELLOW "--long-distance-overhead " WHITE "<exp>" RESET "\n"
           "    Set the time overhead of connecting a long distance call. "
           "Default\n"
           "    is 1200.\n"
           "\n"
           "  " YELLOW "--end-overhead " WHITE "<dur>" RESET "\n"
           "    Set the time it takes the operator to end the call. Default "
           "is 5.\n"
           "\n"
           "  " YELLOW "--ring-timeout " WHITE "<dur>" RESET "\n"
           "    Set the after which the operator will end the ringing phone "
           "because\n"
           "    the calee didn't pick up.\n"
           "\n"
           "  " YELLOW "--p-unknown-number " WHITE "<propability>" RESET "\n"
           "    Set the propability that the called number will be wrong. "
           "Default\n"
           "    is 0.05\n"
           "\n"
           "  " YELLOW "--p-direct " WHITE "<propability>" RESET "\n"
           "    Set the propability that call will be within the same phone\n"
           "    exchange and it can be connected directly. Default is 0.7.\n"
           "\n"
           "  " YELLOW "--p-long-distance " WHITE "<propability>" RESET "\n"
           "    Set the propability that call will be a long distance call. "
           "Default\n"
           "    is 0.1.\n"
           "\n"
           "  " YELLOW "--p-redirect " WHITE "<propability>" RESET "\n"
           "    Set the propability that call will be within the same phone\n"
           "    exchange, but it will have to be redirected to different "
           "operator.\n"
           "    Default is 0.15.\n"
           "\n"
           "  " YELLOW "--out-dst " WHITE "<exp>" RESET "\n"
           "    Set how often outcoming calls will start. Default is 60. "
           "(e.g. 60\n"
           "    is once every 60 seconds)\n"
           "\n"
           "  " YELLOW "--in-dst " WHITE "<exp>" RESET "\n"
           "    Set how often incoming calls will start. Default is 60. (e.g. "
           "60\n"
           "    is once every 60 seconds)\n"
           "\n" GREEN "Notes:" RESET "\n"
           "  All time values are measured in seconds.\n"
           "\n"
           "  The sum of all propabilities doesn't have to be 1, it will be\n"
           "  normalized so that they will sum up to 1.\n"
           "\n"
           "  " WHITE BOLD "Type explanations:" RESET "\n"
           "    " WHITE "<time>             " RESET
           "Absolute time in simulation. Must be "
           "positive.\n"
           "    " WHITE "<file>             " RESET "Path to output file.\n"
           "    " WHITE "<seed>             " RESET "Any value in range from `"
        << std::numeric_limits<long>::min() << "` to `"
        << std::numeric_limits<long>::max()
        << ".\n"
           "    " WHITE "<count>            " RESET "Whole positive number.\n"
           "    " WHITE "<uniform-min>      " RESET
           "Lower bound of uniform distribution.\n"
           "    " WHITE "<uniform-max>      " RESET
           "Upper bound of uniform distribution.\n"
           "    " WHITE "<normal-center>    " RESET
           "Average value of normal distribution.\n"
           "    " WHITE "<normal-deviation> " RESET
           "Standard deviation of normal "
           "distribution.\n"
           "    " WHITE "<exp>              " RESET
           "Expected value of exponential "
           "distribution.\n"
           "    " WHITE "<dur>              " RESET "Fixed duration of time.\n"
           "    " WHITE "<propability>      " RESET "Any positive number.\n";
}
