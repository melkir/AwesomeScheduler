#ifndef AWESOMESCHEDULER_DISPATCHER_H
#define AWESOMESCHEDULER_DISPATCHER_H


#include "socket.h"

class Dispatcher {
public:
    void startServer(const std::string &hostname = "localhost", const uint16_t port = 5001);

    ssize_t receiveFile(int sockfd);

private:
    void doProcessing(int sock);
};


#endif //AWESOMESCHEDULER_DISPATCHER_H
