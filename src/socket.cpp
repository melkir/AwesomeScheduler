#include "socket.h"
#include "util.h"
#include <netdb.h>
#include <cstring>

Socket::Socket(const std::string &hostname, const uint16_t port) {
    /* Create TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    myAssert(sockfd >= 0, "socket()");

    /* Resolve hostname IP by name */
    struct hostent *h = gethostbyname(hostname.c_str());
    myAssert(NULL != h, "gethostbyname()");

    /* Fill in socket structure */
    bzero((char *) &socketAddr, sizeof(socketAddr));
    socketAddr.sin_family = AF_INET;
    memcpy(&socketAddr.sin_addr, h->h_addr, 4);
    socketAddr.sin_port = htons(port);
}

void Socket::_connect() {
    rc = connect(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    myAssert(rc >= 0, "connect()");
}

void Socket::_bind() {
    rc = bind(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    myAssert(rc >= 0, "bind()");
}

void Socket::_listen(int max_co_request) {
    rc = listen(sockfd, max_co_request);
    myAssert(rc >= 0, "listen()");
}

int Socket::_accept(struct sockaddr_in &socketAddr) {
    int theConversation;
    socklen_t size_s = sizeof(socketAddr);
    /* Wait for a client to connect */
    theConversation = accept(sockfd, (sockaddr *) &socketAddr, &size_s);
    myAssert(theConversation >= 0, "accept()");
    return theConversation;
}







