#include "../include/client.h"










/* Error handling & exit. */

void error(const char *msg) {perror(msg); exit(EXIT_FAILURE);}





/* Reads messages until tabspace character appaears. */ 

int readMessage(int *sockFD, char *buffer, size_t size)
{
    int bytesInvolved;


    memset(buffer, 0, size);

    bytesInvolved = read(*sockFD, buffer+strlen(buffer), 1);
    if (bytesInvolved==0) {perror("ERROR: (r) First byte"); return 0;}

    while (buffer[strlen(buffer)-1]!='\t')
    {
        bytesInvolved = read(*sockFD, buffer+strlen(buffer), 1);
        if (bytesInvolved==0) {perror("ERROR: (r) Later bytes"); return 0;}
    }

    memset(buffer+strlen(buffer)-1, 0, 1);

    return 1;
}





/* Writes a message with tabspace character. */

int writeMessage(int *sockFD, char message[])
{
    int bytesInvolved;

    bytesInvolved = write(*sockFD, message, strlen(message));
    if (bytesInvolved<=0) {perror("ERROR: (w) First byte"); return 0;}

    bytesInvolved = write(*sockFD, "\t", 1);
    if (bytesInvolved<=0) {perror("ERROR: (w) Later bytes"); return 0;}

    return 1;
}





/* Main client program. */

int runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[])
{
    /* Variable declarations. */

    int sockFD, bytesInvolved;
    char onlineBuffer[ONLINE_BUFFER_SIZE] = {0};
    char command[COMMAND_MAX_LENGTH] = {0};


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





    /* Sending username to server. */

    printf("STAT: Sending username \"%s\".\n", username);

    if (writeMessage(&sockFD, username)==1) {printf("OK: Username written to socket!\n");}
    else {printf("ERROR: Can't write username to socket!\n");}

    if (readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer))==1)
        printf("STAT: Username socket received is \"%s\".\n", onlineBuffer);

    else
        printf("ERROR: Unable to read stream sent by server!\n");



    /* Sending hostName to server. */

    printf("STAT: Sending host username \"%s\".\n", hostUsername);

    if (writeMessage(&sockFD, hostUsername)==1) {printf("OK: Host username written to socket!\n");}
    else {printf("ERROR: Can't write host username to socket!\n");}

    if (readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer))==1)
        printf("%s\n", onlineBuffer);

    else
        printf("ERROR: Unable to read stream sent by server!\n");



    /* Sending hostPassword to server. */

    printf("STAT: Sending host password \"%s\".\n", hostPassword);

    if (writeMessage(&sockFD, hostPassword)==1) {printf("OK: Host password written to socket!\n");}
    else {printf("ERROR: Can't write host password to socket!\n");}

    if (readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer))==1)
        printf("%s\n", onlineBuffer);

    else
        printf("ERROR: Unable to read stream sent by server!\n");

    printf("\n");





    /* Request-response loop. */

    while (1)
    {
        /* Clean buffer & send the message. */

        printf("TOS> "); fgets(command, sizeof(command), stdin); newline_remover(command);
        writeMessage(&sockFD, command);
        readMessage(&sockFD, buffer, sizeof(buffer));
    }



    /* Closing the socket. */

    close(sockFD);

    return 0;
}