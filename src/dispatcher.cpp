#include "util.h"
#include "dispatcher.h"
#include <iostream>
#include <zconf.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

void Dispatcher::startServer(const string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    const int &sockfd = socket.getFileDescriptor();
    const sockaddr_in &socketAddr = socket.getAddress();

    /* Bind socket to the port */
    int rc = bind(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    myAssert(rc >= 0, "bind()");

    /* Start listening for clients on the socket */
    rc = listen(sockfd, 5);
    myAssert(rc >= 0, "listen()");
    cout << socket << "\n" << "Waiting for incoming connection..." << endl;

    int theConversation;
    struct sockaddr_in clientAddr;
    /* Handle multiple simultaneous connections */
    while (true) {
        socklen_t size_s = sizeof(clientAddr);
        /* Wait for a client to connect */
        theConversation = accept(sockfd, (sockaddr *) &clientAddr, &size_s);
        myAssert(theConversation >= 0, "accept()");
        cout << "A new client has joined the server : "
        << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
        /* Create child process */
        switch (fork()) {
            case -1:
                perror("fork() failed");
                exit(1);
            case 0:
                /* This is the client process */
                close(sockfd);
                doProcessing(theConversation);
                cout << "Client has quit the server" << endl;
                exit(0);
            default:
                /* This is the parent process */
                close(theConversation);
        }
    } /* end of while */
}

void Dispatcher::doProcessing(const int sock) {
    char buffer[256];
    ssize_t read_count, write_count;
    /* Read the client message */
    read_count = read(sock, buffer, 255);
    myAssert(read_count >= 0, "read()");

    /* And print it in the console */
    printf("Server receive : %s", buffer);

    /* Send him an ACK */
    write_count = write(sock, "Server : I got your message", 27);
    myAssert(write_count >= 0, "write()");
    receiveFile(sock);
}

void Dispatcher::receiveFile(const int sockfd) {
    FILE *theIn = fdopen(sockfd, "r");
    myAssert(NULL != theIn, "fdopen()");
    char buffer[256];

    while (!feof(theIn)) {
        fgets(buffer, sizeof(buffer), theIn);
        printf("Server receive : %s", buffer);
    }
    fclose(theIn);
}


int main() {
    Dispatcher dispatcher;
    cout << "-----------------------\n"
    << "Dispatcher as a Server\n"
    << "-----------------------" << endl;
    dispatcher.startServer("localhost", 5002);

    return 0;
}


