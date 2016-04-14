#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingStrategy.h"

class Scheduler {
private:
    SchedulingStrategy &_strategy;
    std::vector<Process *> _processes;
public:
    Scheduler(SchedulingStrategy &strategy);

    void addProcess(const std::string &name);

    void run(int n);
};

#endif
