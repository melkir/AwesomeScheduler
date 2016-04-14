#ifndef AWESOMESCHEDULER_ENDUSER_H
#define AWESOMESCHEDULER_ENDUSER_H


#include "Socket.h"

class EndUser {
public:
    void startClient(const char *hostname = "localhost", const uint16_t port = 5001);

private:
    void doProcessing(int sock);
};


#endif //AWESOMESCHEDULER_ENDUSER_H
