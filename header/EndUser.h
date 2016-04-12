#ifndef AWESOMESCHEDULER_ENDUSER_H
#define AWESOMESCHEDULER_ENDUSER_H


#include "Socket.h"

class EndUser {
public:
    EndUser(const char *hostname = "localhost", const uint16_t port = 5001);

    void startClient();

private:
    void doProcessing(int sock);

    Socket socket;
};


#endif //AWESOMESCHEDULER_ENDUSER_H
