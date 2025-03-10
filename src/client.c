#include "../include/client.h"










/* Error handling & exit. */

void error(const char *msg) {perror(msg); exit(EXIT_FAILURE);}





/* Main client program. */

int runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[])
{
    /* Variable declarations. */

    int sockFD, n;
    char onlineBuffer[ONLINE_BUFFER_SIZE] = {0};


    /* Structure declarations. */

    struct sockaddr_in serverAddress;
    struct hostent *server;


    
    /* Getting socket file descriptor. */

    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0) {error("ERROR opening socket");}


    /* Getting hostname/IP. */

    server = gethostbyname(hostIP);
    if (server == NULL) {fprintf(stderr,"ERROR, no such host\n"); exit(0);}



    /* Server address configuration. */

    memset((char *)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;

    memcpy(
        (char *)&serverAddress.sin_addr.s_addr, 
        (char *)server->h_addr, 
        server->h_length
    );
    serverAddress.sin_port = htons(port);



    /* Connecting the socket to socket address. */

    if (connect(sockFD,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) 
        {error("ERROR");}



    /* Sending various initiation details to server. */

    printf("Sending username: %s...\n", username); write(sockFD, username, strlen(username));
    printf("Sending hostName: %s...\n", hostUsername); write(sockFD, hostUsername, strlen(hostUsername));
    printf("Sending hostPassword: %s...\n", hostPassword); write(sockFD, hostPassword, strlen(hostPassword));



    /* Request-response loop. */

    while (1)
    {
        /* Clean buffer & send the message. */

        memset(onlineBuffer, 0, ONLINE_BUFFER_SIZE);
        printf("Please enter the message: "); fgets(onlineBuffer,255,stdin); newline_remover(onlineBuffer);


        /* Checking for empty commands/messages passed. */

        n = write(sockFD, onlineBuffer, strlen(onlineBuffer));
        if (n < 0) {error("ERROR writing to socket");}

        memset(onlineBuffer, 0, ONLINE_BUFFER_SIZE);


        /* Reading a sent message. */

        n = read(sockFD, onlineBuffer, ONLINE_BUFFER_SIZE-1);
        if (n < 0) {error("ERROR reading from socket");}

        printf("%s\n", onlineBuffer);
    }



    /* Closing the socket. */

    close(sockFD);

    return 0;
}