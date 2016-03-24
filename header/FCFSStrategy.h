#ifndef FCFS_STRATEGY_H
#define FCFS_STRATEGY_H

#include "SchedulingStrategy.h"

/** First Come First Serve Strategy */
class FCFSStrategy : public SchedulingStrategy {
private:
    int _current;

public:
    FCFSStrategy();

    virtual void next(const std::vector<Process *> &processes);
};

#endif
