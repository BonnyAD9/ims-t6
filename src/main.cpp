#include <simlib.h>

#include <vector>
#include <format>
#include <memory>
#include <iostream>

constexpr double RUN_TIME = 1000;

constexpr unsigned long OPERATOR_CNT = 3;
static std::vector<std::unique_ptr<Facility>> operators;

#define DEBUG(...) std::cerr << std::format(__VA_ARGS__) << '\n';

enum class Action {
    UNKNOWN_NUMBER,
    DIRECTLY,
    LONG_DISTANCE,
    REDIRECT,
};

enum {
    ENTER_PRIORITY = 1,
    REDIRECT_PRIORITY,
    END_PRIORITY,
};

class Call : public Process {
public:
    static constexpr double ASK_NUMBER_TIME_MIN = 20;
    static constexpr double ASK_NUMBER_TIME_MAX = 60;

    static constexpr double END_TIME = 5;

    static constexpr double PICK_TIME = 60;
    static constexpr double PICK_DEVIATION = 30;

    static constexpr double CALL_TIME = 5 * 60;

    static constexpr double LONG_DISTANCE_WAIT = 20 * 60;

    Call(Call *redirected = nullptr) : _redirected(redirected), _operator(*operators[static_cast<std::size_t>(Random() * operators.size())]) {}

    void Behavior() override {
        DEBUG("Time: {}", Time);
        Seize(_operator, _redirected ? REDIRECT_PRIORITY : ENTER_PRIORITY);
        Wait(Uniform(ASK_NUMBER_TIME_MIN, ASK_NUMBER_TIME_MAX));
        auto action = get_action();
        switch (action) {
            case Action::UNKNOWN_NUMBER:
                end();
                break;
            case Action::DIRECTLY:
                direct_call();
                break;
            case Action::LONG_DISTANCE:
                long_distance_call();
                break;
            case Action::REDIRECT:
                redirect_call();
                break;
        }
    }

    void ring_timeout() {
        Cancel();
        end();
    }

private:
    void direct_call();

    void long_distance_call() {
        Release(_operator);
        Wait(Exponential(LONG_DISTANCE_WAIT));
        if (Random() < 0.75) {
            Wait(Exponential(CALL_TIME));
        }
        end();
    }

    void redirect_call() {
        Release(_operator);
        (new Call(this))->Activate();
        Passivate();
        end();
    }

    void call() {
        Release(_operator);
        Wait(Exponential(CALL_TIME));
        end();
    }

    void end() {
        Seize(_operator, END_PRIORITY);
        Wait(END_TIME);
        Release(_operator);
        if (_redirected) {
            _redirected->Activate();
        }
        Terminate();
    }

    Action get_action() {
        auto rn = Random();
        if (_redirected) {
            return rn < 0.95 ? Action::DIRECTLY : Action::UNKNOWN_NUMBER;
        }
        if (rn < 0.05) {
            return Action::UNKNOWN_NUMBER;
        }
        if (rn < 0.75) {
            return Action::DIRECTLY;
        }
        if (rn < 0.85) {
            return Action::LONG_DISTANCE;
        }
        return Action::REDIRECT;
    }

    Call *_redirected;
    Facility &_operator;
};

class RingTimeout : public Process {
public:
    static constexpr double RING_TIMEOUT = 120;
    RingTimeout(Call &call) : _call(call) {}

    void Behavior() override {
        Wait(RING_TIMEOUT);
        _call.ring_timeout();
    }

    void cancel() {
        Terminate();
    }

private:
    Call &_call;
};

class OutgoingCall : public Event {
    static constexpr double TIME = 60;

    void Behavior() override {
        DEBUG("Generating: {}", Time);
        (new Call)->Activate();
        Activate(Time + Exponential(TIME));
    }
};


void Call::direct_call() {
    auto wait = Normal(PICK_TIME, PICK_DEVIATION);
    if (wait <= 0) { // User is already calling
        end();
        return;
    }
    auto timeout = new RingTimeout(*this);
    timeout->Activate();
    Release(_operator);
    Wait(wait);
    timeout->cancel();
    call();
}

int main() { // experiment description
    Print("calls - SIMLIB/C++ example\n");
    SetOutput("model.out");
    Init(0, RUN_TIME);
    (new OutgoingCall)->Activate();
    std::vector<std::string> names;
    for (std::size_t i = 0; i < OPERATOR_CNT; ++i) {
        auto s = std::format("operator{}", i);
        s.reserve(sizeof(std::string));
        names.push_back(std::move(s));
        operators.push_back(std::make_unique<Facility>(names.rbegin()->c_str()));
    }
    Run();
    for (auto &op : operators) {
        op->Output();
    }
    return 0;
}
