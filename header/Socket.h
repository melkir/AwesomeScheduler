#ifndef AWESOMESCHEDULER_SOCKET_H
#define AWESOMESCHEDULER_SOCKET_H

#include <netinet/in.h>

class Socket {
public:
    Socket(const char *hostname, uint16_t port);

//    void startClient();
//
//    void startServer();
//
//    virtual void doProcessing(int sock) = 0;

    int getSockFD() const { return sockfd; }

    const sockaddr_in &getSocketAddr() const { return socketAddr; }

private:
    int sockfd;
    struct sockaddr_in socketAddr;
};


#endif //AWESOMESCHEDULER_SOCKET_H
