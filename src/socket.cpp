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