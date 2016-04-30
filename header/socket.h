#ifndef AWESOMESCHEDULER_SOCKET_H
#define AWESOMESCHEDULER_SOCKET_H

#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <zconf.h>

#define MAX_SIZE 1024

class Socket {
public:
    Socket(const std::string &hostname, const uint16_t port);

    void _connect();

    void _bind();

    void _listen(int max_connection_request);

    int _accept(struct sockaddr_in &clientAddr);

    int getFileDescriptor() const { return sockfd; }

    const sockaddr_in &getAddress() const { return socketAddr; }

    friend std::ostream &operator<<(std::ostream &os, const Socket &s) {
        return os << inet_ntoa(s.getAddress().sin_addr) << ":" << ntohs(s.getAddress().sin_port);
    }

    ~Socket() {
        std::cerr << "~Socket() called" << std::endl;
        close(sockfd);
    };

private:
    int sockfd;
    int rc;
    struct sockaddr_in socketAddr;
};

#endif //AWESOMESCHEDULER_SOCKET_H
