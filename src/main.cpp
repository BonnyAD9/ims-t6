#include <simlib.h>

#include "call.hpp"
#include "config.hpp"
#include "outgoing_call.hpp"

void start() { // experiment description
    Print("calls - SIMLIB/C++ example\n");
    SetOutput("model.out");

    Config conf;
    conf.init();

    Init(0, conf.run_time);
    (new OutgoingCall(conf))->Activate();
    Run();
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
