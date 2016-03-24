#ifndef RR_STRATEGY_H
#define RR_STRATEGY_H

#include "SchedulingStrategy.h"

/** Round Robin Strategy */
class RRStrategy : public SchedulingStrategy {
private:
    int _current;

public:
    RRStrategy();

    virtual void next(const std::vector<Process *> &processes);
};

#endif
