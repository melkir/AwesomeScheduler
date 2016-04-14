#ifndef AWESOMESCHEDULER_DISPATCHER_H
#define AWESOMESCHEDULER_DISPATCHER_H


#include "Socket.h"

class Dispatcher {
public:
    void startServer(const char *hostname = "localhost", const uint16_t port = 5001);
private:
    void doProcessing(int sock);
};


#endif //AWESOMESCHEDULER_DISPATCHER_H
