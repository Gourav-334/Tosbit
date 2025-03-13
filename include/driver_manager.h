#ifndef DRIVER_MANAGER
	#define DRIVER_MANAGER


#define TRUE 1
#define FALSE 0

#define HOSTNAME_MAX_LENGTH 33
#define HOSTPASSWORD_MAX_LENGTH 33
#define ONLINE_BUFFER_SIZE 1025
#define COMMAND_MAX_LENGTH 512



#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "encrypter.h"
#include "utility_box.h"
#include "syntax_parser.h"










/* Declarations */

static int connected = FALSE;
static int interpretLoop = FALSE;
static int sockFD = 0;
static char onlineBuffer[ONLINE_BUFFER_SIZE] = {0};


/* Structure declarations. */

static struct sockaddr_in serverAddress;
static struct hostent *server;










/* Functions */

extern void error(const char *msg);
extern int readMessage(int *sockFD, char *buffer, size_t size);
extern int writeMessage(int *sockFD, char message[]);
extern void runClient(
	char username[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[],
	int takeover
);
extern void setConnection(
	char username[],
	char password[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[],
	int takeover
);
extern void interpret(char *user_cmd);
extern void endConnection();





#endif