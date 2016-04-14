#include <sys/socket.h>
#include <util.h>
#include <zconf.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include "end_user.h"

using namespace std;

void EndUser::startClient(const char *hostname, const uint16_t port) {
    Socket socket(hostname, port);
    const int &sockfd = socket.getFileDescriptor();
    const sockaddr_in &socketAddr = socket.getAddress();

    /* Connect to the server */
    int connect_return = connect(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    Util::myAssert(connect_return >= 0, "connect()");

    cout << "Connection established with the server : " << socket << endl;

    doProcessing(sockfd);
    close(sockfd);
}

void EndUser::doProcessing(int sock) {
    /* Ask for a message from the user, this message will be read by the server */
    char buffer[256];
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    /* Send the message to the server */
    ssize_t write_count = write(sock, buffer, strlen(buffer));
    Util::myAssert(write_count >= 0, "write()");

    /* Read the server response */
    bzero(buffer, 256);
    ssize_t read_count = read(sock, buffer, 255);
    Util::myAssert(read_count >= 0, "read()");

    /* And print it in the console */
    printf("%s\n", buffer);
}

int main() {
    EndUser endUser;
    cout << "--------------------\n"
    << "End-User as a Client\n"
    << "--------------------" << endl;
    endUser.startClient("localhost", 5001);
}


