#include <sys/socket.h>
#include <util.h>
#include <zconf.h>
#include <iostream>
#include <sys/sendfile.h>
#include <strings.h>
#include <cstring>
#include <task_properties.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "end-user.h"

using namespace std;

void EndUser::startClient(const string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    /* Connect to the server */
    socket._connect();
    cout << "Connection established with the server : " << socket << endl;
    /* Start processing on this socket */
    doProcessing(socket.getFileDescriptor());
}

void EndUser::doProcessing(int sock) {
    /* Ask for a message from the user, this message will be read by the server */
    char buffer[256];
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    /* Send the message to the server */
    ssize_t write_count = write(sock, buffer, strlen(buffer));
    myAssert(write_count >= 0, "write()");

    /* Read the server response */
    bzero(buffer, 256);
    ssize_t read_count = read(sock, buffer, 255);
    myAssert(read_count >= 0, "read()");

    /* And print it in the console */
    printf("%s\n", buffer);

    int option;
    string path;
    TaskProperties t;
    do {
        //Displaying Options for the menu
        cout << "1) Load a task from XML\n"
        << "2) Create a task\n"
        << "3) Exit" << endl;
        //Prompting user to enter an option according to the menu
        cout << "Please select an option : ";
        cin >> option;  // taking option value as input and saving in variable "option"
        switch (option) {
            case 1 :
                cout << "Enter the path to the xml file :";
                cin >> path;
                t.load(path);
                sendFile(sock, path);
                break;
            case 2:
                cout << "Create the properties file :" << endl;
                t.load();
                cout << "Save the XML in which directory ? ";
                cin >> path;
                t.save(path);
                sendFile(sock, path);
                break;
            case 3:
                cout << "Closing connection with the server..." << endl;
                close(sock);
                break;
            default:
                cout << "Invalid option entered" << endl;
        }
        cout << string(2, '\n');
    } while (option != 3);  //condition of do-while loop
}

void EndUser::sendFile(const int sockfd, const string &filepath) {
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
    /* close descriptor for file that was sent */
    close(fd);
}


int main() {
    EndUser endUser;
    cout << "--------------------\n"
    << "End-User as a Client\n"
    << "--------------------" << endl;
//    endUser.promptMenu();
    endUser.startClient("localhost", 5002);

    return 0;
}


