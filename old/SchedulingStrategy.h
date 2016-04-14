#ifndef SCHEDULING_STRATEGY_H
#define SCHEDULING_STRATEGY_H

#include <vector>
#include "Process.h"

class SchedulingStrategy {
public:
    virtual void next(const std::vector<Process *> &processes) = 0;
};

#endif
