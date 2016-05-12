#include <fstream>
#include <memory.h>
#include <tkPort.h>
#include <sys/sendfile.h>
#include "util.h"
#include "dispatcher.h"

#define SOCK_CLOSED 0
#define SOCK_MAX_CLIENT 5
#define EXIT_SUCCESS 0
#define EXIT_ERROR 1
#define NB_WORKER 4

using namespace std;

void Dispatcher::startServer(const string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    /* Bind socket to the port */
    socket._bind();
    /* Start listening for clients on the socket */
    socket._listen(SOCK_MAX_CLIENT);
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
                exit(EXIT_ERROR);
            case 0:
                /* This is the client process */
                close(socket.getFileDescriptor());
                doProcessing(theConversation);
                cout << "Client " << ntohs(clientAddr.sin_port) << " has quit the server" << endl;
                startClient("localhost", 6000);
                exit(EXIT_SUCCESS);
            default:
                /* This is the parent process */
                close(theConversation);
        }
    } /* end of while */
}

void Dispatcher::doProcessing(const int sock) {
    /* Receive new tasks files until the socket close */
    while (receiveTask(sock) != SOCK_CLOSED);
}

ssize_t Dispatcher::receiveTask(const int sock) {
    char buffer[MAX_SIZE];
    ssize_t size = read(sock, &buffer, MAX_SIZE);
    myAssert(size >= 0, "read()");

    // if read return 0 it's mean that socket has been closed by the clients
    if (0 == size) return SOCK_CLOSED;
    buffer[size] = '\0';

    TaskProperties tp;
    const string &str(buffer);

    // load the task from the buffer
    tp.load_buffer(str);

    // and add it to the task queue
    m_taskQueue.push(tp);
    return size;
}

void Dispatcher::startClient(const string &hostname, const uint16_t port) {
    cout << "-----------------------\n"
    << "Dispatcher as a Client\n"
    << "-----------------------" << endl;
    Socket socket(hostname, port);
    /* Connect to the server */
    socket._connect();
    cout << "Connection established with the worker : " << socket << endl;
    /* Start processing on this socket */
    doProcessingWorker(socket.getFileDescriptor());
}

void Dispatcher::sendFile(const int sockfd, const string &filepath) {
    int fd;                     /* file descriptor for file to send */
    struct stat stat_buf;       /* argument to fstat */
    off_t offset = 0;           /* file offset */
    /* open the file in read-only mode */
    fd = open(filepath.c_str(), O_RDONLY);
    myAssert(-1 != fd, "open()");
    /* get the size of the file to be sent */
    fstat(fd, &stat_buf);
    /* copy file using sendfile */
    cout << "Sending the task to the server..." << endl;
    ssize_t rc = sendfile(sockfd, fd, &offset, (size_t) stat_buf.st_size);
    myAssert(-1 != rc, "sendfile()");
    if (rc != stat_buf.st_size) {
        fprintf(stderr, "incomplete transfer from sendfile: %li of %li bytes\n", rc, stat_buf.st_size);
        exit(1);
    }
    cout << "File sent successfully" << endl;
    /* close descriptor for file task that was sent */
    close(fd);
    /* delete the file task since we don't need it anymore */
    unlink(filepath.c_str());
}

void Dispatcher::doProcessingWorker(int sock) {
//    /* Ask for a message from the user, this message will be read by the server */
//    char buffer[256];
//    printf("Please enter the message: ");
//    bzero(buffer, 256);
//    fgets(buffer, 255, stdin);
//
//    /* Send the message to the server */
//    ssize_t write_count = write(sock, buffer, strlen(buffer));
//    myAssert(write_count >= 0, "write()");
//
//    /* Read the server response */
//    bzero(buffer, 256);
//    ssize_t read_count = read(sock, buffer, 255);
//    myAssert(read_count >= 0, "read()");
//
//    /* And print it in the console */
//    printf("%s\n", buffer);

    while (!m_taskQueue.empty()) {
        // envoi de la tache sur le worker
        TaskProperties tp = m_taskQueue.top();
        string path = tp.save();
        sendFile(sock, path);
        m_taskQueue.pop();

        char buffer[256];
        /* Read the server response */
        bzero(buffer, 256);
        ssize_t read_count = read(sock, buffer, 255);
        myAssert(read_count >= 0, "read()");
        buffer[256] = '\0';
        printf("%s\n", buffer);
    }

}

int main() {
    Dispatcher dispatcher;
    cout << "-----------------------\n"
    << "Dispatcher as a Server\n"
    << "-----------------------" << endl;
    dispatcher.startServer("localhost", 5002);

    return 0;
}


