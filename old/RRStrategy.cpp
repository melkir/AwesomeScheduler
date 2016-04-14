#include "RRStrategy.h"

RRStrategy::RRStrategy() : _current(-1) { }

// TODO Implement a timer which does the context switch after each Nth time slice (each time slice is 1/N duration)
void RRStrategy::next(const std::vector<Process *> &processes) {
    // only active if there are processes
    if (processes.size() > 0) {
        if (_current < 0) {
            // special initial handling
            _current = 0;
        }
        else {
            processes[_current]->suspend();
            _current++;
            _current %= processes.size();
        }
        processes[_current]->resume();
    }
}
