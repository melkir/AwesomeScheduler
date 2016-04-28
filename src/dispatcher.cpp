#include "util.h"
#include "dispatcher.h"

using namespace std;

void Dispatcher::startServer(const string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    /* Bind socket to the port */
    socket._bind();
    /* Start listening for clients on the socket */
    socket._listen(5);
    cout << socket << "\n" << "Waiting for incoming connection..." << endl;

    int theConversation;
    struct sockaddr_in clientAddr;
    /* Handle multiple simultaneous connections */
    while (true) {
        /* Wait for a client to connect */
        theConversation = socket._accept(clientAddr);
        cout << "A new client has joined the server : "
        << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
        /* Create child process */
        switch (fork()) {
            case -1:
                perror("fork() failed");
                exit(1);
            case 0:
                /* This is the client process */
                close(socket.getFileDescriptor());
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
//    char buffer[256];
//    ssize_t read_count, write_count;
//    /* Read the client message */
//    read_count = read(sock, buffer, 255);
//    myAssert(read_count >= 0, "read()");
//
//    /* And print it in the console */
//    printf("Server receive : %s\n", buffer);
//
//    /* Send him an ACK */
//    write_count = write(sock, "Server : I got your message", 27);
//    myAssert(write_count >= 0, "write()");

    /* Receive new tasks files until the socket close */
    while (receiveFile(sock) != 0);
}

ssize_t Dispatcher::receiveFile(const int sock) {
    char buffer[MAX_SIZE];
    ssize_t size = read(sock, &buffer, MAX_SIZE);
    myAssert(size >= 0, "read()");
    buffer[size] = '\0';
    cout << buffer << endl;
    return size;
}


int main() {
    Dispatcher dispatcher;
    cout << "-----------------------\n"
    << "Dispatcher as a Server\n"
    << "-----------------------" << endl;
    dispatcher.startServer("localhost", 5002);

    return 0;
}


