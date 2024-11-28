#include <chrono>

#include <simlib.h>

#include "call.hpp"
#include "cli/args.hpp"
#include "cli/help.hpp"
#include "config.hpp"
#include "incoming_call.hpp"
#include "outgoing_call.hpp"

void start(Args args) {
    if (args.help) {
        help();
        return;
    }

    if (args.rng_seed) {
        RandomSeed(*args.rng_seed);
    } else {
        RandomSeed(
            long(std::chrono::system_clock::now().time_since_epoch().count())
        );
    }

    if (args.output) {
        SetOutput(args.output->c_str());
    }

    PRINTLN("SIMLIB/C++ - Telephone Exchange");

    Config conf = std::move(args.config);
    conf.init();

    Init(0, conf.run_time);
    (new OutgoingCall(conf))->Activate();
    (new IncomingCall(conf))->Activate();
    Run();
    conf.output();
    for (auto &op : conf.operators) {
        op->output();
    }
}

int main(int argc, char **argv) {
    try {
        start(Args({ argv, std::size_t(argc) }));
    } catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "An error occured\n";
        return EXIT_FAILURE;
    }
}
