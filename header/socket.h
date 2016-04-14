#ifndef AWESOMESCHEDULER_SOCKET_H
#define AWESOMESCHEDULER_SOCKET_H

#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

class Socket {
public:
    Socket(const std::string &hostname, const uint16_t port);

    int getFileDescriptor() const { return sockfd; }

    const sockaddr_in &getAddress() const { return socketAddr; }

    friend std::ostream &operator<<(std::ostream &os, const Socket &s) {
        return os << inet_ntoa(s.getAddress().sin_addr) << ":" << ntohs(s.getAddress().sin_port);
    }

private:
    int sockfd;
    struct sockaddr_in socketAddr;
};

#endif //AWESOMESCHEDULER_SOCKET_H
