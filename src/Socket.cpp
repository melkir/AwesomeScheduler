#include "Socket.h"
#include "Util.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <netdb.h>
#include <cstring>
#include <zconf.h>

using namespace std;

Socket::Socket(const char *hostname, const uint16_t port) {
    /* Create TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    Util::myAssert(sockfd >= 0, "socket()");

    /* Resolve hostname IP by name */
    struct hostent *h = gethostbyname(hostname);
    Util::myAssert(NULL != h, "gethostbyname()");

    /* Initialize the socket structure */
    bzero((char *) &socketAddr, sizeof(socketAddr));
    socketAddr.sin_family = AF_INET;
    memcpy(&socketAddr.sin_addr, h->h_addr, 4);
    socketAddr.sin_port = htons(port);
}