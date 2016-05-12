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
    char buffer[MAX_SIZE];
    ssize_t size;
    /* Read the client message */
    size = read(sock, &buffer, MAX_SIZE);
    myAssert(size >= 0, "read()");
    buffer[size] = '\0';

    TaskProperties tp;
    const string &str(buffer);
    tp.load_buffer(str);
    cout << "J'ai recu la tâche " << tp.getProcedureName()
    << "\nDébut du travail..." << endl;
    sleep(8);
    cout << "Travail terminé" << endl;

    string ack = "Worker : Travail fini";
    /* Send him an ACK */
    size = write(sock, "Worker : Travail fini", ack.size());
    myAssert(size >= 0, "write()");
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