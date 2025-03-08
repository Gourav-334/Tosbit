#ifndef CLIENT_H
    #define CLIENT_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>



#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 512
#define MAX_EVENTS 10





/* Structure to hold buffer for reading and writing data. */

typedef struct
{
    char read_buffer[BUFFER_SIZE];      // Buffer for incoming data
    size_t read_pos;                    // Position in the read buffer
    char write_buffer[BUFFER_SIZE];     // Buffer for outgoing data
    size_t write_pos;                   // Position in the write buffer
} client_buffer_t;





/* Function declarations. */

void cleanup_client(void);
void handle_signal(int sig);
int start_socket_client(const char *ip_address, int port, void (*signal_handler)(int));
static int set_nonblocking(int sockfd);
static void handle_server_response(void);
static void handle_user_input(void);





/* External variables that need to be shared. */

extern int client_socket;
extern char server_ip[16];
extern int epoll_fd;
extern volatile int running;
extern client_buffer_t buffer;





#endif
