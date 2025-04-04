/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/driver_manager.h"










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

void runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[], int takeover)
{
    /* Variable declarations. */

    int bytesInvolved;
    char *user_cmd = NULL;



    /* Managing takeover by Tosbit. */

    interpretLoop = takeover;

    
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



    /* Sending client's location to server. */

    getLocation(); printf("STAT: Sending location \"%s\".\n", loc);

    if (writeMessage(&sockFD, loc)==1) {printf("OK: Location written to socket!\n");}
    else {printf("ERROR: Can't write location to socket!\n");}

    if (readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer))==1)
        printf("STAT: Location socket received is \"%s\".\n", onlineBuffer);

    else
        printf("ERROR: Unable to read stream sent by server!\n");

    printf("\n");





    /* Checking if takeover was requested & return if so. */

    if (takeover==FALSE) {return;}





    /* Read history of entered inputs. */

    read_history(".my_history");
    clear_history();


    /* Request-response loop. */

    while (1)
    {
        /* Clean buffer & send the message. */

        user_cmd = readline("TOS> ");
        add_history(user_cmd); write_history(".my_history");

        bytesInvolved = write(sockFD, user_cmd, strlen(user_cmd));
        if (bytesInvolved<=0) {perror("ERROR: (w) First byte"); return;}

        readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer));
        printf("%s\n\n", onlineBuffer);
    }



    /* Closing the socket. */

    close(sockFD);
}










/* Connects to the database. */

void setConnection(char username[], char password[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[], int takeover)
{
	/* Declarations */

	FILE *fptr;
	char c;

	char codedUsername[MAX_ENCRYPTED_SIZE] = {0};
	char codedPassword[MAX_ENCRYPTED_SIZE] = {0};



	/* Checking if the username exists. */

	fptr = fopen("users/user.tosbit", "r");


	if (fptr==NULL) {printf("ERROR: Can't find user credential file!\n"); return;}
    else if (newFile(fptr))
    {
        account = FALSE;
        printf("ERROR: Please create your user account by running engine first!\n");
        return;
    }


	/* Fetching encrypted username & password. */

	c = fgetc(fptr);
	while (c!='\n') {codedUsername[strlen(codedUsername)] = c; c = fgetc(fptr);}

	c = fgetc(fptr);
	while (!reachedEOF(fptr)) {codedPassword[strlen(codedPassword)] = c; c = fgetc(fptr);}

	fclose(fptr);


	/* Confirming details on terminal screen. */

	if (!strcmp(username,decrypt(codedUsername)) && !strcmp(password,decrypt(codedPassword)))
	{
        /*
         * WARNING: Fix value of 'username' changing before & after this 'if' statement.
         * Problem might be in shared buffers or static string in 'decrypt()'.
         */

		printf("STAT: Checking credentials for host %s...\n", hostUsername);
		runClient(decrypt(codedUsername), hostIP, port, hostUsername, hostPassword, takeover);
	}
	else {printf("ERROR: Username or password doesn't match!\n"); account = FALSE; return;}
}










/* Interprets a passed command. */

void interpret(char *user_cmd)
{
    /* Checking for account existence. */

    if (account==FALSE) {printf("ERROR: Account must exist for using \"interpret()\"!\n"); return;}


	/* Declarations */

	int bytesInvolved;


	/* Writing if interpretor mode is ON. */

	bytesInvolved = write(sockFD, user_cmd, strlen(user_cmd));
    if (bytesInvolved<=0) {perror("ERROR: (w) First byte"); return;}

    printf("TOS> %s\n", user_cmd);

    readMessage(&sockFD, onlineBuffer, sizeof(onlineBuffer));
    printf("%s\n\n", onlineBuffer);
}










/* End the current connection by closing the socket. */

void endConnection()
{
    /* Checking for account existence. */

    if (account==FALSE) {printf("ERROR: No successful connection opened yet!\n"); return;}

    close(sockFD);
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */