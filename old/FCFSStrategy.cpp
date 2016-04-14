#include "FCFSStrategy.h"

FCFSStrategy::FCFSStrategy() : _current(-1) { }

void FCFSStrategy::next(const std::vector<Process *> &processes) {
    // only active if there are processes
    if (processes.size() > 0) {
        if (_current < 0) {
            // special initial handling
            _current = 0;
        } else {
            processes[_current]->suspend();
            _current++;
        }
        processes[_current]->resume();
    }
}
