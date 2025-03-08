#include "../include/server.h"





/* Global variables. */

client_t *clients[MAX_CLIENTS]; // It is the array to keep tracks of the connected clients.
int server_socket;              // It is a file descriptor for the server socket the server use this socket to listen for client connection.
int epoll_fd;                   // File descriptor for the epoll instance.





/* Function prototypes. */

static int set_nonblocking(int sockfd);         // Sets a socket to non blocking mode it takes the socket file descriptor as parameter.
static client_t* add_client(int client_socket, struct sockaddr_in addr);    // Add new client to the clients array and initializes its structure.
static void remove_client(client_t* client);    // Remove a client from the aforementioned array and free its memory.
static void handle_new_connection(int server_socket);// Handles new client connection which is incoming
static void handle_client_data(client_t* client);   // Handles clients data.

void cleanup_server(void);                      // Cean up server resources when shutting down.
void handle_signal(int sig);                    // Signale handler function like ctrl+ c to work.





/* Signal handler for graceful shutdown. */

void handle_signal(int sig)
{
    /* Takes signal number as parameter  eg 2 which denotes ctrl + c so when i do ctrl+c it cleans up the server. */

    printf("\nShutting down server...\n");


    /* Call cleanup function to close sockets and free resources. */

    cleanup_server();
    exit(0);
}





/* Function to set socket to non-blocking mode. */

static int set_nonblocking(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);  // Get the current flags of the socket file descriptor.
    

    if (flags == -1)
    {
        /* Checks fctnl is working or not because this is used to get fd or modify it. */

        perror("fcntl F_GETFL");        // u will understand -> Ofcourse
        return -1;                      // u know this right -> Yes sir
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        /* Set the   socket to non blocking mode by adding  O_NONBLOCK to its flag. */

        perror("fcntl F_SETFL O_NONBLOCK");
        return -1;
    }


    return 0;
}





/* Function to add a new client. */

static client_t* add_client(int client_socket, struct sockaddr_in addr)
{
    /* So lets see how can we add clients in the array. */

    client_t* client = (client_t*)malloc(sizeof(client_t));     // Allocate memory for new client structure.

    if (!client) {perror("Failed to allocate client structure"); return NULL;}



    /* So we store new client information the client_t array that we declared. */

    client->socket = client_socket;         // Assign the client socket descriptor.
    client->address = addr;                 // Store the client's address information.
    client->buffer_used = 0;                // Initialize buffer usage to zero.



    /* Add to clients array. */

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        /* We loop through the  clients slots. */

        if (clients[i] == NULL)
        {
            /* If we find empty space. */

            clients[i] = client;    // Assign the new client to the empty slots.
            break;
        }
    }


    return client;      // Return the pointer to the newly added client.
}





/* Till now we saw the pointer is is been now waiting for new client but he was not able to find one so lets explore. */

/* Function to remove a client. */

static void remove_client(client_t* client)
{
    /* Taking the array as pointer. */

    if (!client) return;        // so return if the pointer is NULL.


    /* Remove from clients array. */

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        /* Loop to find and remove the client. */

        if (clients[i] == client)
        {
            /* So if one client wants to go we need to find him and say goodbye. */

            clients[i] = NULL;
            break;
        }
    }



    close(client->socket);      // Then we need to close the client to free the resources.
    free(client);               // Free the allocated spaces provided to him.
}





/* Function to handle new client connection. */

static void handle_new_connection(int server_socket)
{
    struct sockaddr_in client_addr;             // Structure to store the clients address gourav this is the ip address of the clients pc ok i hope u understand.
    socklen_t client_len = sizeof(client_addr); //store the size of the clients address.



    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len); // Accept new connection.
    
    if (client_socket < 0)
    {
        /* If no request. */

        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            /* So we dont want our epoll to wait for infinity so we give them this error to make it nonblocking. */

            perror("Accept failed");
        }

        return;
    }



    /* Set client socket to non-blocking mode. */

    if (set_nonblocking(client_socket) < 0)
    {
        /* Set the new socket to non blocking mode i have already explained. */

        close(client_socket);       // If it fails then close it.
        return;
    }



    /* Create new client structure. */

    client_t* client = add_client(client_socket, client_addr);  // Return a new client structure and it to the clients array.
    

    /* If memory allocation fails then close it. */

    if (!client) {close(client_socket); return;}



    /* Add client socket to epoll. */

    struct epoll_event ev;          // Prepare an epoll event to monitor client's socket.
    ev.events = EPOLLIN | EPOLLET;  // Its like an alert so that we wont need to check so whenever the data is ready it will inform us.
    ev.data.ptr = client;           // it is like marking the the specific clients which are stored it in client_t array so that we dont need to struggle finding that.



    /* Add the client's socket to the epoll instance for monitoring. */

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev) < 0)
    {
        perror("epoll_ctl: client_socket");
        remove_client(client);
        return;
    }



    /* Convert port number to host byte order because it is necessary or else we wont be able to recognize port number. */

    printf(
        "New client connected from %s:%d\n", 
        inet_ntoa(client_addr.sin_addr),        // It is used to convert the ip address into human readable format.
        ntohs(client_addr.sin_port)
    );


    /* Send welcome message. */

    const char* welcome = "Welcome to the server!\n";
    send(client_socket, welcome, strlen(welcome), 0);   // Send the welcome message over the socket.
}





/* Function to handle client data - This will be provided by Tosbit. */

static void handle_client_data(client_t* client)
{
    while (1)
    {
        /*
         * Read data from the client's socket into the buffer.
         * It reads up to the available buffer space (BUFFER_SIZE - buffer_used).
         */

        ssize_t bytes_read = read(
            client->socket,
            client->buffer + client->buffer_used,
            BUFFER_SIZE - client->buffer_used
        );



        if (bytes_read < 0)
        {
            /*
             * If the error is EAGAIN or EWOULDBLOCK, it means there is no more data to read.
             * In this case, we simply break out of the loop and wait for more data later.
             */

            if (errno == EAGAIN || errno == EWOULDBLOCK) {break;}


            /* Any other error is critical, so we log it and remove the client. */

            perror("read"); remove_client(client);
            return;
        }



        if (bytes_read == 0) {printf("Client disconnected\n"); remove_client(client); return;}

        /* Forward the received data to Tosbit's command processor. */
        /* Tosbit will implement this part. */

        client->buffer_used = 0;        // Reset buffer after processing.
    }
}





/* Main socket server function that Tosbit will use. */

int start_socket_server(int port, void(*client_handler)(client_t*))
{
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);



    /* Create epoll instance. */

    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {perror("epoll_create1"); return -1;}


    /* Create server socket. */

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {perror("Socket creation failed"); return -1;}


    /* Set server socket to non-blocking mode. */

    if (set_nonblocking(server_socket) < 0) {close(server_socket); return -1;}



    /* Configure server address. */

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);


    /* Bind to all available network interfacesb which helps us to accept any ip address. */

    server_addr.sin_addr.s_addr = INADDR_ANY;



    /* Bind the server address. */

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        /* We need to bind the server for specific port to listen for communication. */

        perror("Binding failed"); close(server_socket);
        return -1;
    }


    /* Listen for incoming connections. */

    if (listen(server_socket, SOMAXCONN) < 0) {
        perror("Listen failed");
        close(server_socket);
        return -1;
    }



    /* Add server socket to epoll. */

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;  
    ev.data.fd = server_socket;


    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &ev) < 0)
    {
        perror("epoll_ctl: server_socket");
        close(server_socket);

        return -1;
    }

    printf("Server is running on port %d...\n", port);



    /* Event loop: Continuously monitor and process incoming events. */

    struct epoll_event events[MAX_EVENTS];      // Array to store triggered events.



    while (1)
    {
        /* Infinite loop to keep the server running. */
        /* Wait for events on the epoll instance, blocking indefinitely (-1 timeout). */
        /* nfds stores the number of file descriptors that have events. */

        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);


        /* If epoll_wait returns a negative value, an error occurred. */

        if (nfds < 0)
        {
            /* If interrupted by a signal (like SIGINT), restart epoll_wait. */

            if (errno == EINTR) {continue;}
            perror("epoll_wait"); break;
        }


        /* Loop through each triggered event. */

        for (int i = 0; i < nfds; i++)
        {
            /* Check if the event corresponds to the server socket (new connection request). */


            /* Accept the new client connection and register it with epoll. */

            if (events[i].data.fd == server_socket) {handle_new_connection(server_socket);}
            else
            {
                /* Existing client has sent data or has an event. */
                /* Retrieve the client structure from the event's data pointer. */

                client_t* client = (client_t*)events[i].data.ptr;
                client_handler(client);
            }
        }
    }


    /* Cleanup */

    cleanup_server();
    return 0;
}





/* Clean up server resources. */

void cleanup_server(void)
{
    close(epoll_fd);
    close(server_socket);


    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i]) {remove_client(clients[i]);}
    }
}





/* Simple main function for testing. */

int main(void)
{
    /* Declarations */

    char c;
    char password[MAX_ENCRYPTED_SIZE] = {0};



    /* Setting up file pointer to user.tosbit */

    FILE *fptr = fopen("users/user.tosbit", "r");
    if (fptr==NULL) {printf("ERROR: File with server credentials not found!\n\n"); return EXIT_FAILURE;}


    /* Fetch the password on local file-system. */

    c = fgetc(fptr);
    while (c!='\n') {password[strlen(password)] = c; fgetc(fptr);}


    /* Close the file pointer safely. */

    fclose(fptr);



    /* Runs the server on loop. */

    return start_socket_server(PORT, handle_client_data);
}