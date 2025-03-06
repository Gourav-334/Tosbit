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

/* Structure to hold client information */
typedef struct {
    int socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    size_t buffer_used;
} client_t;

/* Global variables */
client_t *clients[MAX_CLIENTS];
int server_socket;
int epoll_fd;

/* Function prototypes */
static int set_nonblocking(int sockfd);
static client_t* add_client(int client_socket, struct sockaddr_in addr);
static void remove_client(client_t* client);
static void handle_new_connection(int server_socket);
static void handle_client_data(client_t* client);
void cleanup_server(void);
void handle_signal(int sig);

/* Signal handler for graceful shutdown */
void handle_signal(int sig) {
    printf("\nShutting down server...\n");
    cleanup_server();
    exit(0);
}

/* Function to set socket to non-blocking mode */
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

/* Function to add a new client */
static client_t* add_client(int client_socket, struct sockaddr_in addr) {
    client_t* client = (client_t*)malloc(sizeof(client_t));
    if (!client) {
        perror("Failed to allocate client structure");
        return NULL;
    }

    client->socket = client_socket;
    client->address = addr;
    client->buffer_used = 0;

    // Add to clients array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == NULL) {
            clients[i] = client;
            break;
        }
    }

    return client;
}

/* Function to remove a client */
static void remove_client(client_t* client) {
    if (!client) return;

    // Remove from clients array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == client) {
            clients[i] = NULL;
            break;
        }
    }

    close(client->socket);
    free(client);
}

/* Function to handle new client connection */
static void handle_new_connection(int server_socket) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    if (client_socket < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Accept failed");
        }
        return;
    }

    // Set client socket to non-blocking mode
    if (set_nonblocking(client_socket) < 0) {
        close(client_socket);
        return;
    }

    // Create new client structure
    client_t* client = add_client(client_socket, client_addr);
    if (!client) {
        close(client_socket);
        return;
    }

    // Add client socket to epoll
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;  
    ev.data.ptr = client;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev) < 0) {
        perror("epoll_ctl: client_socket");
        remove_client(client);
        return;
    }

    printf("New client connected from %s:%d\n", 
           inet_ntoa(client_addr.sin_addr), 
           ntohs(client_addr.sin_port));

    // Send welcome message
    const char* welcome = "Welcome to the server!\n";
    send(client_socket, welcome, strlen(welcome), 0);
}

/* Function to handle client data - This will be provided by Tosbit */
static void handle_client_data(client_t* client) {
    
    while (1) {
        ssize_t bytes_read = read(client->socket, 
                                client->buffer + client->buffer_used,
                                BUFFER_SIZE - client->buffer_used);

        if (bytes_read < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            perror("read");
            remove_client(client);
            return;
        }

        if (bytes_read == 0) {
            printf("Client disconnected\n");
            remove_client(client);
            return;
        }

        // Forward the received data to Tosbit's command processor
        // Tosbit will implement this part
        client->buffer_used = 0;  // Reset buffer after processing
    }
}

/* Main socket server function that Tosbit will use */
int start_socket_server(int port, void(*client_handler)(client_t*)) {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        return -1;
    }

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set server socket to non-blocking mode
    if (set_nonblocking(server_socket) < 0) {
        close(server_socket);
        return -1;
    }

    // Configure server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the server address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_socket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, SOMAXCONN) < 0) {
        perror("Listen failed");
        close(server_socket);
        return -1;
    }

    // Add server socket to epoll
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;  
    ev.data.fd = server_socket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &ev) < 0) {
        perror("epoll_ctl: server_socket");
        close(server_socket);
        return -1;
    }

    printf("Server is running on port %d...\n", port);

    // Event loop
    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds < 0) {
            if (errno == EINTR) continue;  // Interrupted by signal
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_socket) {
                // New connection
                handle_new_connection(server_socket);
            } else {
                // Client data available
                client_t* client = (client_t*)events[i].data.ptr;
                client_handler(client);
            }
        }
    }

    // Cleanup
    cleanup_server();
    return 0;
}

/* Clean up server resources */
void cleanup_server(void) {
    close(epoll_fd);
    close(server_socket);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            remove_client(clients[i]);
        }
    }
}

/* Simple main function for testing */
int main(void) {
    return start_socket_server(PORT, handle_client_data);
}