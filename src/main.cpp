#include <chrono>

#include <simlib.h>

#include "call.hpp"
#include "config.hpp"
#include "incoming_call.hpp"
#include "outgoing_call.hpp"

void start() {
    RandomSeed(long(std::chrono::system_clock::now().time_since_epoch().count()
    ));

    SetOutput("model.out");
    PRINTLN("SIMLIB/C++ - Telephone Exchange");

    Config conf;
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

int main() {
    try {
        start();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "An error occured\n";
        return EXIT_FAILURE;
    }
}
