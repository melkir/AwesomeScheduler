//----------------------------------------------------------------------
//----------------------------------------------------------------------
//
//		------------
//		 Dispacher:
//		------------
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <zconf.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <cassert>
#include <netdb.h>
#include <cstring>

using namespace std;

namespace {

    void doProcessing(int sock) {
        char buffer[256];

        /* Read the client message */
        ssize_t read_count = read(sock, buffer, 255);
        assert(read_count >= 0 && "read()");

        /* And print it in the console */
        printf("Server receive : %s\n", buffer);

        /* Send him an ACK */
        ssize_t write_count = write(sock,"I got your message",18);
        assert(write_count >= 0 && "write()");
    }

    void exec() {
        /* Server address and port number */
        struct hostent *h = gethostbyname("localhost");
        assert(NULL != h && "gethostbyname()");
        uint16_t num_port = 5001;

        /* Create socket */
        int theConnection = socket(AF_INET, SOCK_STREAM, 0);
        assert(theConnection >= 0 && "socket()");

        /* Initialize the server socket structure */
        struct sockaddr_in serv_addr;
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        memcpy(&serv_addr.sin_addr, h->h_addr, 4);
        serv_addr.sin_port = htons(num_port);

        /* Bind the host address */
        if (bind(theConnection, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("bind() failed");
            exit(1);
        }

        /* Start listening for the clients, here process will
         * go in sleep mode and will wait for the incoming connection
         */
        if (listen(theConnection, 5) < 0) {
            perror("listen() failed");
            exit(1);
        }

        int theConversation;
        struct sockaddr_in client_addr;
        /* Handle multiple simultaneous connections */
        while (true) {
            socklen_t size_s = sizeof(client_addr);
            theConversation = accept(theConnection, (sockaddr *) &client_addr, &size_s);
            if (theConversation < 0) {
                perror("accept() failed");
                exit(1);
            }
            /* Create child process */
            switch (fork()) {
                case -1:
                    perror("fork() failed");
                    exit(1);
                case 0:
                    /* This is the client process */
                    close(theConnection);
                    doProcessing(theConversation);
                    exit(0);
                default:
                    /* This is the parent process */
                    close(theConversation);
            }
        } /* end of while */
    }

}

int main(int argc, char *argv[]) {
    cout << "-----------------------\n"
    << " Dispatcher as a Server: \n"
    << "-----------------------" << endl;

    exec();

    return 0;
}
