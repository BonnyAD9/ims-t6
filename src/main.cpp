#include <simlib.h>

// global objects:
static Facility box("Box");
constexpr double TABLE_WAIT_STEP = 25;
constexpr double TABLE_WAIT_STEP_COUNT = 20;
static Histogram table("Table", 0, TABLE_WAIT_STEP, TABLE_WAIT_STEP_COUNT);

class Customer : public Process {
    static constexpr double SERVICE_TIME = 10;

    double _arrival;            // atribute of each customer
    void Behavior() override {  // --- behavoir specification ---
        _arrival = Time;        // incoming time
        Seize(box);             // start of service
        Wait(SERVICE_TIME);     // time of service
        Release(box);           // end of service
        table(Time - _arrival); // waiting and service time
    }
};

constexpr double MIDDLE_WAIT_TIME = 1e3 / 150;

class Generator : public Event {    // model of system's input
    void Behavior() override {      // --- behavior specification ---
        (new Customer)->Activate(); // new customer
        Activate(Time + Exponential(MIDDLE_WAIT_TIME)); //
    }
};

constexpr double RUN_TIME = 1000;

int main() { // experiment description
    Print(" model2 - SIMLIB/C++ example\n");
    SetOutput("model2.out");
    Init(0, RUN_TIME);           // experiment initialization for time 0..1000
    (new Generator)->Activate(); // customer generator
    Run();                       // simulation
    box.Output();                // print of results
    table.Output();
    return 0;
}
