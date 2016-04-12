#ifndef AWESOMESCHEDULER_DISPATCHER_H
#define AWESOMESCHEDULER_DISPATCHER_H


#include "Socket.h"

class Dispatcher {
public:
    Dispatcher(const char *hostname = "localhost", const uint16_t port = 5001);

    void startServer();

private:
    void doProcessing(int sock);

    Socket socket;
};


#endif //AWESOMESCHEDULER_DISPATCHER_H
