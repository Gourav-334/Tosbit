#ifndef SERVER_H
    #define SERVER_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>



#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10
#define MAX_CLIENTS 1024





/* Client structure. */

typedef struct {
    int socket;                     // Client socket file descriptor.
    struct sockaddr_in address;     // Client address information.
    char buffer[BUFFER_SIZE];       // Buffer to store received data.
    size_t buffer_used;             // Amount of data currently in buffer.
} client_t;





/* External variables that need to be shared. */

extern client_t *clients[MAX_CLIENTS];
extern int server_socket;
extern int epoll_fd;





/* Public function declarations. */

int start_socket_server(int port, void(*client_handler)(client_t*));
void cleanup_server(void);
void handle_signal(int sig);





#endif
