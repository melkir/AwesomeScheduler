#include "Util.h"
#include "Dispatcher.h"
#include <iostream>
#include <zconf.h>
#include <arpa/inet.h>

using namespace std;

void Dispatcher::startServer(const char *hostname, const uint16_t port) {
    Socket socket(hostname, port);
    const int &sockfd = socket.getFileDescriptor();
    const sockaddr_in &socketAddr = socket.getAddress();

    /* Bind the host address */
    int bind_return = bind(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    Util::myAssert(bind_return >= 0, "bind()");

    /* Start listening for clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */
    int listen_return = listen(sockfd, 5);
    Util::myAssert(listen_return >= 0, "listen()");
    cout << socket << "\n" << "Waiting for incoming connection..." << endl;

    int theConversation;
    struct sockaddr_in clientAddr;
    /* Handle multiple simultaneous connections */
    while (true) {
        socklen_t size_s = sizeof(clientAddr);
        theConversation = accept(sockfd, (sockaddr *) &clientAddr, &size_s);
        Util::myAssert(theConversation >= 0, "accept()");
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

void Dispatcher::doProcessing(int sock) {
    char buffer[256];
    ssize_t read_count, write_count;
    /* Read the client message */
    read_count = read(sock, buffer, 255);
    Util::myAssert(read_count >= 0, "read()");

    /* And print it in the console */
    printf("Server receive : %s", buffer);

    /* Send him an ACK */
    write_count = write(sock, "Server : I got your message", 27);
    Util::myAssert(write_count >= 0, "write()");
}

int main() {
    Dispatcher dispatcher;
    cout << "-----------------------\n"
    << "Dispatcher as a Server\n"
    << "-----------------------" << endl;
    dispatcher.startServer("localhost", 5001);
}


