#ifndef AWESOMESCHEDULER_DISPATCHER_H
#define AWESOMESCHEDULER_DISPATCHER_H


#include <queue>
#include "socket.h"
#include "task_properties.h"

typedef TaskProperties task_t;


class Dispatcher {
public:
    void startServer(const std::string &hostname = "localhost", const uint16_t port = 5001);

    ssize_t receiveTask(int sockfd);

    void startClient(const string &hostname, const uint16_t port);

private:
    void doProcessing(int sock);

    void doProcessingWorker(int sock);

    std::priority_queue<task_t, std::vector<task_t>, std::less<task_t>> m_taskQueue;
};


#endif //AWESOMESCHEDULER_DISPATCHER_H
