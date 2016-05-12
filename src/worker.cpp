#include <cstdint>
#include <worker.h>
#include <zconf.h>
#include <util.h>
#include <socket.h>

#define SOCK_CLOSED 0
#define SOCK_MAX_CLIENT 5
#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

using namespace std;

void Worker::startServer(const std::string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    /* Bind socket to the port */
    socket._bind();
    /* Start listening for clients on the socket */
    socket._listen(SOCK_MAX_CLIENT);
    cout << socket << "\n" << "Waiting for incoming connection..." << endl;

    int theConversation;
    struct sockaddr_in clientAddr;
    /* Wait for a client to connect */
    theConversation = socket._accept(clientAddr);
    cout << "A new client has joined the server : "
    << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;

    close(socket.getFileDescriptor());
    receiveTask(theConversation);
}


long Worker::receiveTask(int sockfd) {
//    char buffer[256];
//    ssize_t read_count, write_count;
//    /* Read the client message */
//    read_count = read(sockfd, buffer, 255);
//    myAssert(read_count >= 0, "read()");
//
//    /* And print it in the console */
//    printf("Server receive : %s\n", buffer);
//
//    /* Send him an ACK */
//    write_count = write(sockfd, "Server : I got your message", 27);
//    myAssert(write_count >= 0, "write()");
    return 0;
}

int main() {
    Worker worker;
    worker.startServer("localhost", 6000);

    return 0;
}