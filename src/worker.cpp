#include <cstdint>
#include <worker.h>
#include <zconf.h>
#include <util.h>
#include <socket.h>
#include <task_properties.h>

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

//    close(socket.getFileDescriptor());
    receiveTask(theConversation);
}


long Worker::receiveTask(int sock) {
    char buffer[256];
    ssize_t read_count;
    /* Read the client message */
    read_count = read(sock, buffer, 255);
    myAssert(read_count >= 0, "read()");
//
//    /* And print it in the console */
//    printf("Worker receive : %s\n", buffer);
//
//    /* Send him an ACK */
//    write_count = write(sock, "Server : I got your message", 27);
//    myAssert(write_count >= 0, "write()");
    buffer[read_count] = '\0';

    TaskProperties tp;
    const string &str(buffer);
    tp.load_buffer(str);
    cout << "J'ai recu la tâche " << tp.getProcedureName()
    << " je travaille dessus..." << endl;
    sleep(10);
    cout << "J'ai fini" << endl;
    return 0;
}

int main() {
    Worker worker;
    cout << "-----------------------\n"
    << "  Worker as a Server\n"
    << "-----------------------" << endl;
    worker.startServer("localhost", 6000);

    return 0;
}