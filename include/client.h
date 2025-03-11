#ifndef CLIENT_H
	#define CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "utility_box.h"
#include "syntax_parser.h"


#define ONLINE_BUFFER_SIZE 1025
#define COMMAND_MAX_LENGTH 512





/* Function declarations. */

extern void error(const char *msg);
extern int readMessage(int *sockFD, char *buffer, size_t size);
extern int writeMessage(int *sockFD, char message[]);
extern int runClient(
	char username[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[]
);





#endif