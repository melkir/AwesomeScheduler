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
#include <netdb.h>
#include <cstring>

using namespace std;

namespace {

    void myAssert(bool condition, const char *message) {
        if (condition) return;
        perror(message);
        exit(1);
    }

    int createTCPSocket(struct sockaddr_in &serv_addr, const char *addr = "localhost", uint16_t num_port = 5001) {
        /* Server address and port number */
        struct hostent *h = gethostbyname(addr);
        myAssert(NULL != h, "gethostbyname()");

        /* Create socket */
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        myAssert(sockfd >= 0, "socket()");

        /* Initialize the server socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        memcpy(&serv_addr.sin_addr, h->h_addr, 4);
        serv_addr.sin_port = htons(num_port);
        return sockfd;
    }

    void doProcessing(int sock) {
        char buffer[256];
        ssize_t read_count, write_count;
        /* Read the client message */
        read_count = read(sock, buffer, 255);
        myAssert(read_count >= 0, "read()");

        /* And print it in the console */
        printf("Server receive : %s", buffer);

        /* Send him an ACK */
        write_count = write(sock, "I got your message", 18);
        myAssert(write_count >= 0, "write()");
    }

    void startServer() {
        struct sockaddr_in serv_addr;
        /* Create the TCP socket localhost:5001 */
        int sockfd = createTCPSocket(serv_addr);
        /* Bind the host address */
        int bind_return = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        myAssert(bind_return >= 0, "bind()");

        /* Start listening for clients, here process will
         * go in sleep mode and will wait for the incoming connection
         */
        int listen_return = listen(sockfd, 5);
        myAssert(listen_return >= 0, "listen()");
        cout << "Waiting for incoming connection..." << endl;

        int theConversation;
        struct sockaddr_in client_addr;
        /* Handle multiple simultaneous connections */
        while (true) {
            socklen_t size_s = sizeof(client_addr);
            theConversation = accept(sockfd, (sockaddr *) &client_addr, &size_s);
            myAssert(theConversation >= 0, "accept()");
            cout << "A new client has connected" << endl;
            /* Create child process */
            switch (fork()) {
                case -1:
                    perror("fork() failed");
                    exit(1);
                case 0:
                    /* This is the client process */
                    close(sockfd);
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

    startServer();

    return 0;
}
