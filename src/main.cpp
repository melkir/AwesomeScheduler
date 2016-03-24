#include <Scheduler.h>
#include <FCFSStrategy.h>

int main() {
    FCFSStrategy fcfs;
    Scheduler scheduler(fcfs);
    scheduler.addProcess("A");
    scheduler.addProcess("B");
    scheduler.addProcess("C");
    scheduler.addProcess("D");
    scheduler.run(8);
    return 0;
}
