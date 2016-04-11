//----------------------------------------------------------------------
//----------------------------------------------------------------------
//
//		------------
//		 Dispacher:
//		------------
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------


#include <iostream>
#include <zconf.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

using namespace std;

namespace {

    void doProcessing(int sock) {

    }

    void exec() {
        int sockfd, newsockfd, port;
        struct sockaddr_in serv_addr, client_addr;
        char buffer[256];

        /* First call to socket() function */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        /* Initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));
        port = 5000;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons((uint16_t) port);

        /* Now bind the host address using bind() call */
        bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

        /* Now start listening for the clients, here process will
         * go in sleep mode and will wait for the incoming connection
         */
        listen(sockfd, 5);

        while (true) {
            newsockfd = accept(sockfd, (sockaddr *) &client_addr, (socklen_t *) sizeof(&client_addr));
            /* Create child process */
            switch (fork()) {
                case -1:
                    perror("ERROR on fork");
                    exit(1);
                case 0:
                    /* This is the client process */
                    close(sockfd);
                    doProcessing(newsockfd);
                    exit(0);
                default:
                    /* This is the parent process */
                    close(newsockfd);
            }
        } /* end of while */
    }

}

int main(int argc, char *argv[]) {
    cout << "-----------------------\n"
    << " Dispatcher as a Server: \n"
    << "-----------------------" << endl;

    exec();

    return 0;
}
