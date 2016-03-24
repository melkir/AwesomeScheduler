#include <Scheduler.h>

Scheduler::Scheduler(SchedulingStrategy &strategy) : _strategy(strategy), _processes() { }

void Scheduler::addProcess(const std::string &name) {
    _processes.push_back(new Process(name));
}

void Scheduler::run(int n) {
    while (--n > 0) _strategy.next(_processes);
}
