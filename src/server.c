#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#include "../include/utility_box.h"
#include "../include/encrypter.h"


#define MAX_EVENTS 10
#define ONLINE_BUFFER_SIZE 1025










/* Error handling function for 'print & exit'. */

void error(const char *msg) {perror(msg); exit(1);}





/* Set socket to non-blocking mode. */

void set_nonblocking(int sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}





/* The main window which keeps running. */

int main(int argc, char *argv[])
{
    /* Variable declarations. */

    FILE *fptr; char c;
    char guestUsername[MAX_DECRYPTED_SIZE] = {0};
    char codedUsername[MAX_ENCRYPTED_SIZE] = {0};
    char codedPassword[MAX_ENCRYPTED_SIZE] = {0};

    char buffer[ONLINE_BUFFER_SIZE] = {0};

    int sockFD, newsockFD, portno, epollFD;
    ssize_t bytesInvolved;


    /* Structure declarations (including epoll() ones). */

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    struct epoll_event event, events[MAX_EVENTS];



    /* Fetching password for host. */

    fptr = fopen("users/user.tosbit", "r");

    c = fgetc(fptr);
    while (c!='\n') {codedUsername[strlen(codedUsername)] = c; c = fgetc(fptr);}
    while (!reachedEOF(fptr)) {codedPassword[strlen(codedPassword)] = c; c = fgetc(fptr);}
    fclose(fptr);



    /* Confirming details on terminal screen. */

    printf("Username: %s\n", decrypt(codedUsername));
    printf("Password: %s\n", decrypt(codedPassword));



    /* Handling less than minimum arguments. */

    if (argc < 2) {fprintf(stderr, "ERROR, no port provided\n"); exit(1);}


    /* Establishing a socket with error handling. */

    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0) {error("ERROR opening socket");}


    /* Setting socket file descriptor to 'non-blocking'. */

    set_nonblocking(sockFD);


    /* Setting socket configurations. */

    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);



    /* Binding socket to configured settings. */

    if (bind(sockFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {error("ERROR on binding");}


    /* Listen for connections. */

    listen(sockFD, 5);



    /* Create epoll instance. */

    epollFD = epoll_create1(0);
    if (epollFD == -1) {error("ERROR creating epoll");}


    /* Add server socket to epoll. */

    event.events = EPOLLIN;
    event.data.fd = sockFD;

    if (epoll_ctl(epollFD, EPOLL_CTL_ADD, sockFD, &event) == -1)
        {error("ERROR adding socket to epoll");}

    printf("Server listening on port %d...\n", portno);





    /* Main request-response loop. */

    while (1)
    {
        /* Epoll file descriptor. */

        int num_fds = epoll_wait(epollFD, events, MAX_EVENTS, -1);
        if (num_fds == -1) {error("ERROR in epoll_wait");}


        for (int i = 0; i < num_fds; i++)
        {
            int fd = events[i].data.fd;


            /* Accepting a new incoming request. */

            if (fd == sockFD)
            {
                clilen = sizeof(cli_addr);
                newsockFD = accept(sockFD, (struct sockaddr *)&cli_addr, &clilen);

                if (newsockFD == -1) {perror("ERROR on accept"); continue;}


                /* Setting the new request to non-blocking too. */

                set_nonblocking(newsockFD);

                event.events = EPOLLIN | EPOLLET;   // Edge-triggered mode
                event.data.fd = newsockFD;

                if (epoll_ctl(epollFD, EPOLL_CTL_ADD, newsockFD, &event) == -1)
                    {error("ERROR adding new client to epoll");}

                printf("New client connected: FD %d\n", newsockFD);





                /* Receiving guestUsername. */

                do {
                    bytesInvolved = read(newsockFD, guestUsername+strlen(guestUsername), 1);
                    if (bytesInvolved<=0) {printf("ERROR: Can't read sent guesUsername!\n");}
                } while (guestUsername[strlen(guestUsername)-1]!='\n');

                newline_remover(guestUsername);
                printf("STAT: Guest username %s received.\n", guestUsername);

                bytesInvolved = write(
                    newsockFD,
                    "OK: Local username received.\n",
                    strlen("OK: Local username received.\n")
                );
                if (bytesInvolved<=0) {printf("ERROR: Can't write acknowledgment!\n");}



                /* Receiving & verifying local username. */

                do {
                    bytesInvolved = read(newsockFD, buffer+strlen(buffer), 1);
                    if (bytesInvolved<=0) {printf("ERROR: Can't read sent local username!\n");}
                } while (buffer[strlen(buffer)-1]!='\n');

                newline_remover(buffer);
                printf("STAT: Host username %s received.\n", buffer);

                if (strcmp(buffer,decrypt(codedUsername)))
                {
                    bytesInvolved =  write(
                        newsockFD,
                        "ERROR: Host username is incorrect!\n",
                        strlen("ERROR: Host username is incorrect!\n")
                    );
                    if (bytesInvolved<=0) {printf("ERROR: Can't write acknowledgment!\n");}

                    printf("STAT: FD %d gave wrong username.\n", newsockFD);
                    close(newsockFD);
                }
                else {printf("STAT: FD %d entered right username.\n", newsockFD);}



                /* Receiving & verifying local password. */

                memset(buffer, 0, sizeof(buffer));

                do {
                    bytesInvolved = read(newsockFD, buffer+strlen(buffer), 1);
                    if (bytesInvolved<=0) {printf("ERROR: Can't read sent local password!\n");}
                } while (buffer[strlen(buffer)-1]!='\n');

                newline_remover(buffer);
                printf("STAT: Guest password %s received.\n", buffer);

                if (strcmp(buffer,decrypt(codedPassword)))
                {
                    bytesInvolved = write(
                        newsockFD,
                        "ERROR: Host password is incorrect!\n",
                        strlen("ERROR: Host password is incorrect!\n")
                    );
                    if (bytesInvolved<=0) {printf("ERROR: Can't write acknowledgment!\n");}

                    printf("STAT: FD %d gave wrong password.\n", newsockFD);
                    close(newsockFD);
                }
                else {printf("STAT: FD %d entered right password.\n", newsockFD);}
            }



            /* Existing client sent data. */

            else
            {
                memset(buffer, 0, sizeof(buffer));
                bytesInvolved = read(fd, buffer, sizeof(buffer)-1);


                /* Handling client disconnection. */

                if (bytesInvolved <= 0)
                {
                    printf("Client FD %d disconnected\n", fd);
                    close(fd);
                    epoll_ctl(epollFD, EPOLL_CTL_DEL, fd, NULL);
                }
                else
                {
                    printf("Received from client FD %d: %s\n", fd, buffer);
                    write(fd, "I got your message", 18);
                }
            }
        }
    }



    /* Closing the server's socket & epoll file descriptor. */

    close(sockFD); close(epollFD);

    return 0;
}
