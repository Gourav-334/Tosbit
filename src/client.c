#include "../include/client.h"










/* Error handling & exit. */

void error(const char *msg) {perror(msg); exit(EXIT_FAILURE);}





/* Main client program. */

int runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[])
{
    /* Variable declarations. */

    int sockFD, bytesInvolved;
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



    /* Sending various initiation details to server (username, hostUsername & hostPassword). */

    printf("Sending username: %s...\n", username);
    bytesInvolved = write(sockFD, username, strlen(username));
    write(sockFD, "\n", 1);     // Delimiter indicator.

    if (bytesInvolved<=0) {printf("ERROR: Can't write username to socket!\n");}
    else {printf("OK: Username written to socket!\n");}


    printf("Sending hostName: %s...\n", hostUsername);
    bytesInvolved = write(sockFD, hostUsername, strlen(hostUsername));
    write(sockFD, "\n", 1);     // Delimiter indicator.

    if (bytesInvolved<=0) {printf("ERROR: Can't write hostUsername to socket!\n");}
    else {printf("OK: hostUsername written to socket!\n");}


    printf("Sending hostPassword: %s...\n", hostPassword);
    bytesInvolved = write(sockFD, hostPassword, strlen(hostPassword));
    write(sockFD, "\n", 1);     // Delimiter indicator.

    if (bytesInvolved<=0) {printf("ERROR: Can't write hostPassword to socket!\n");}
    else {printf("OK: hostPassword written to socket!\n");}



    /* Request-response loop. */

    while (1)
    {
        /* Clean buffer & send the message. */

        memset(onlineBuffer, 0, sizeof(onlineBuffer));
        printf("Please enter the message: "); printf("(%s)\n", onlineBuffer);
        fgets(onlineBuffer, sizeof(onlineBuffer), stdin); newline_remover(onlineBuffer);


        /* Checking for empty commands/messages passed. */

        bytesInvolved = write(sockFD, onlineBuffer, strlen(onlineBuffer)-1);
        if (bytesInvolved < 0) {continue;}

        memset(onlineBuffer, 0, sizeof(onlineBuffer));


        /* Reading a sent message. */

        bytesInvolved = read(sockFD, onlineBuffer, strlen(onlineBuffer));
        if (bytesInvolved < 0) {error("ERROR reading from socket");}

        printf("%s\n", onlineBuffer);
    }



    /* Closing the socket. */

    close(sockFD);

    return 0;
}