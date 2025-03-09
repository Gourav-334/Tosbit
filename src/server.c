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

#define MAX_EVENTS 10
#define BUFFER_SIZE 256

void error(const char *msg) {
    perror(msg);
    exit(1);
}

// Set socket to non-blocking mode
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, epoll_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    struct epoll_event event, events[MAX_EVENTS];

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    set_nonblocking(sockfd);

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
        error("ERROR creating epoll");

    // Add server socket to epoll
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event) == -1)
        error("ERROR adding socket to epoll");

    printf("Server listening on port %d...\n", portno);

    while (1) {
        int num_fds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_fds == -1)
            error("ERROR in epoll_wait");

        for (int i = 0; i < num_fds; i++) {
            int fd = events[i].data.fd;

            if (fd == sockfd) { // New incoming connection
                clilen = sizeof(cli_addr);
                newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
                if (newsockfd == -1) {
                    perror("ERROR on accept");
                    continue;
                }

                set_nonblocking(newsockfd);
                event.events = EPOLLIN | EPOLLET; // Edge-triggered mode
                event.data.fd = newsockfd;

                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, newsockfd, &event) == -1)
                    error("ERROR adding new client to epoll");

                printf("New client connected: FD %d\n", newsockfd);

            } else { // Existing client sent data
                char buffer[BUFFER_SIZE];
                bzero(buffer, BUFFER_SIZE);
                int n = read(fd, buffer, BUFFER_SIZE - 1);

                if (n <= 0) { // Client disconnected
                    printf("Client FD %d disconnected\n", fd);
                    close(fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                } else {
                    printf("Received from client FD %d: %s\n", fd, buffer);
                    write(fd, "I got your message", 18);
                }
            }
        }
    }

    close(sockfd);
    close(epoll_fd);
    return 0;
}
