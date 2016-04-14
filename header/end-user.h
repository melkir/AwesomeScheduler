#ifndef AWESOMESCHEDULER_ENDUSER_H
#define AWESOMESCHEDULER_ENDUSER_H


#include "socket.h"

class EndUser {
public:
    void startClient(const string &hostname = "localhost", const uint16_t port = 5001);

    void promptMenu(int sock);

    void sendFile(int sock, const string &filepath);

private:
    void doProcessing(int sock);
};


#endif //AWESOMESCHEDULER_ENDUSER_H
