

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


int client_socket;
char server_ip[16];
int epoll_fd;
volatile int running = 1;


void cleanup_client(void);
void handle_signal(int sig);
int start_socket_client(const char *ip_address, int port, void (*signal_handler)(int));
static int set_nonblocking(int sockfd);


typedef struct {
    char read_buffer[BUFFER_SIZE];
    size_t read_pos;
    char write_buffer[BUFFER_SIZE];
    size_t write_pos;
} client_buffer_t;

client_buffer_t buffer = {0};


static int set_nonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
        return -1;
    }
    return 0;
}


void handle_signal(int sig) {
    printf("\nDisconnecting from server...\n");
    running = 0;
}


static void handle_server_response(void) {
    while (1) {
        ssize_t bytes_read = read(client_socket, 
                                buffer.read_buffer + buffer.read_pos,
                                BUFFER_SIZE - buffer.read_pos);

        if (bytes_read < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break; 
            }
            perror("read");
            running = 0;
            return;
        }

        if (bytes_read == 0) {
            printf("Server disconnected\n");
            running = 0;
            return;
        }

        buffer.read_pos += bytes_read;
        
        
        char* newline;
        while ((newline = memchr(buffer.read_buffer, '\n', buffer.read_pos))) {
            size_t line_length = newline - buffer.read_buffer + 1;
            ssize_t bytes_written = write(STDOUT_FILENO, buffer.read_buffer, line_length);
            if (bytes_written < 0) {
                perror("write");
                running = 0;
                return;
            }
            if ((size_t)bytes_written < line_length) {
                fprintf(stderr, "Partial write occurred\n");
                running = 0;
                return;
            }
            
            
            memmove(buffer.read_buffer, newline + 1, 
                    buffer.read_pos - line_length);
            buffer.read_pos -= line_length;
        }

        
        if (buffer.read_pos == BUFFER_SIZE) {
            ssize_t bytes_written = write(STDOUT_FILENO, buffer.read_buffer, buffer.read_pos);
            if (bytes_written < 0) {
                perror("write");
                running = 0;
                return;
            }
            if ((size_t)bytes_written < buffer.read_pos) {
                fprintf(stderr, "Partial write occurred\n");
                running = 0;
                return;
            }
            buffer.read_pos = 0;
        }
    }
}


static void handle_user_input(void) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    
    set_nonblocking(STDIN_FILENO);

    while (running) {
        read = getline(&line, &len, stdin);
        
        if (read == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                
                handle_server_response();
                usleep(10000);  
                continue;
            }
            break;
        }

        
        if (strncmp(line, "exit", 4) == 0) {
            running = 0;
            break;
        }

        
        ssize_t bytes_sent = send(client_socket, line, read, 0);
        if (bytes_sent < 0) {
            perror("send");
            break;
        }
    }

    free(line);
}


int start_socket_client(const char *ip_address, int port, void (*signal_handler)(int)) {
    
    strncpy(server_ip, ip_address, sizeof(server_ip) - 1);
    server_ip[sizeof(server_ip) - 1] = '\0';

    
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    struct sockaddr_in server_addr;

    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    
    if (set_nonblocking(client_socket) < 0) {
        close(client_socket);
        return -1;
    }

    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    
    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        perror("Invalid server IP address");
        return -1;
    }

   
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        if (errno != EINPROGRESS) {
            perror("Connection failed");
            return -1;
        }
    }

    printf("Connected to server at %s:%d\n", ip_address, port);

   
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        return -1;
    }

    
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;  
    ev.data.fd = client_socket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev) < 0) {
        perror("epoll_ctl: client_socket");
        return -1;
    }

    
    handle_user_input();

    
    cleanup_client();
    return 0;
}


void cleanup_client(void) {
    close(client_socket);
    close(epoll_fd);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        printf("Example: %s 192.168.1.100\n", argv[0]);
        exit(1);
    }

    return start_socket_client(argv[1], SERVER_PORT, handle_signal);
}
