/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef DRIVER_MANAGER
	#define DRIVER_MANAGER


#define TRUE 	1 			// Macro to imitate boolean TRUE behaviour.
#define FALSE 	0 			// Macro to imitate boolean FALSE behaviour.

#define HOSTNAME_MAX_LENGTH 	33 			// Server host name's length limit.
#define HOSTPASSWORD_MAX_LENGTH 33  		// Server host password's length limit.
#define ONLINE_BUFFER_SIZE 		1025  		// Online buffer's size for read operations.
#define COMMAND_MAX_LENGTH 		512  		// User input command length limit.





#include <errno.h>					// Error handling header.
#include <stdio.h>					// Standard input/output header.
#include <stdlib.h>					// Standard library functionalities header.
#include <unistd.h>					// UNIX operations header.
#include <string.h>					// String utility header.
#include <fcntl.h>					// File control header.
#include <sys/types.h>				// Special data types header.
#include <sys/socket.h>				// Central socket header.
#include <netinet/in.h>				// Internet protocol header.
#include <netdb.h>					// Network database operations header.
#include <termios.h>				// Disabling ECHO to hide password.

#include "encrypter.h"				// Encryption & decryption header.
#include "utility_box.h"			// Custom utility functions header.
#include "syntax_parser.h"			// DFA-based syntax parser header.










/* Declarations */

static int connected 		= FALSE;		// Tells if a remote database is being accessed.
static int interpretLoop 	= FALSE;		// Tells if database command loop is there or not.
static int sockFD 			= 0;			// Socket file descriptor for client-side.


static char onlineBuffer[ONLINE_BUFFER_SIZE] = {0};		// Buffer to receive data from server.



/* Structure declarations. */

static struct sockaddr_in serverAddress;		// Structure to hold server address information.
static struct hostent *server;					// Structure to hold client's information.










/* Functions */

extern void error(const char *msg);				// Error handling & exit.
extern int readMessage(							// Reads messages until tabspace character appaears.
	int *sockFD,
	char *buffer,
	size_t size
);
extern int writeMessage(						// Writes a message with tabspace character.
	int *sockFD,
	char message[]
);
extern void runClient(							// Main client program.
	char username[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[],
	int takeover
);
extern void setConnection(						// Connects to the database.
	char username[],
	char password[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[],
	int takeover
);
extern void interpret(char *user_cmd);			// Interprets a passed command.
extern void endConnection();					// End the current connection by closing the socket.





#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */