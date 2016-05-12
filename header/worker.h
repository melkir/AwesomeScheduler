#ifndef AWESOMESCHEDULER_WORKER_H
#define AWESOMESCHEDULER_WORKER_H

#include <cstdint>
#include <iostream>

class Worker {
public:
    void startServer(const std::string &hostname, const uint16_t port);

    ssize_t receiveTask(int sockfd);

private:

};

#endif //AWESOMESCHEDULER_WORKER_H
