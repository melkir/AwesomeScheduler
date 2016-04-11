//----------------------------------------------------------------------
//----------------------------------------------------------------------
//
//		-----------
//		 End-User:
//		-----------
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <strings.h>
#include <cassert>
#include <netdb.h>
#include <cstring>
#include <zconf.h>

using namespace std;

namespace {

    void doProcessing(int sock) {
        /* Ask for a message from the user, this message will be read by the server */
        char buffer[256];
        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        /* Send the message to the server */
        ssize_t write_count = write(sock, buffer, strlen(buffer));
        assert(write_count >= 0 && "write()");

        /* Read the server response */
        bzero(buffer, 256);
        ssize_t read_count = read(sock, buffer, 255);
        assert(read_count >= 0 && "read()");

        /* And print it in the console */
        printf("%s\n", buffer);
    }

    void exec() {
        /* Server address and port number */
        struct hostent *h = gethostbyname("localhost");
        assert(NULL != h && "gethostbyname()");
        uint16_t num_port = 5001;

        /* Create socket */
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0 && "socket()");

        /* Initialize the server socket structure */
        struct sockaddr_in serv_addr;
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        memcpy(&serv_addr.sin_addr, h->h_addr, 4);
        serv_addr.sin_port = htons(num_port);

        /* Connect to the server */
        int connect_return = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        assert(connect_return >= 0 && "connect()");

        doProcessing(sockfd);
    }
}

int main(int argc, char *argv[]) {
    cout << "-----------------------\n"
    << " End-User as a Client: \n"
    << "-----------------------" << endl;

    exec();

    return 0;
}
