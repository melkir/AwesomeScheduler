#include <sys/socket.h>
#include <util.h>
#include <zconf.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include <task_properties.h>
#include "end-user.h"

using namespace std;

void EndUser::startClient(const string &hostname, const uint16_t port) {
    Socket socket(hostname, port);
    const int &sockfd = socket.getFileDescriptor();
    const sockaddr_in &socketAddr = socket.getAddress();

    /* Connect to the server */
    int connect_return = connect(sockfd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    myAssert(connect_return >= 0, "connect()");

    cout << "Connection established with the server : " << socket << endl;

    doProcessing(sockfd);
    close(sockfd);
}

void EndUser::doProcessing(int sock) {
    promptMenu(sock);
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
}

void EndUser::promptMenu(int sock) {
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
                break;
            case 2:
                cout << "Create the properties file :" << endl;
                t.load();
                cout << "Save the XML in which directory ? ";
                cin >> path;
                t.save(path);
                break;
            case 3:
                cout << "Closing connection with the server..." << endl;
                break;
            default:
                cout << "Invalid option entered" << endl;
        }
        sendFile(sock, path);
        cout << string(2, '\n');
    } while (option != 3);  //condition of do-while loop
}

void EndUser::sendFile(const int sockfd, const string &filepath) {
    FILE *taskFile = fopen(filepath.c_str(), "r");
    myAssert(NULL != taskFile, "fopen()");
    FILE *theOut = fdopen(sockfd, "w");
    myAssert(NULL != theOut, "fdopen()");
    char buffer[255];
    fgets(buffer, sizeof(buffer), taskFile);
    while (!feof(taskFile)) {
        fputs(buffer, theOut);
        fflush(theOut);
        fgets(buffer, sizeof(buffer), taskFile);
        cout << "send : " << buffer << endl;
    }
//    fclose(taskFile);
//    fclose(theOut);
}


int main() {
    EndUser endUser;
    cout << "--------------------\n"
    << "End-User as a Client\n"
    << "--------------------" << endl;
//    endUser.promptMenu();
    endUser.startClient("localhost", 5002);
}


