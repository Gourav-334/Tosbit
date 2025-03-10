#ifndef CLIENT_H
	#define CLIENT_H


#define ONLINE_BUFFER_SIZE 1025



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "utility_box.h"





/* Function declarations. */

extern void error(const char *msg);
extern int runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[]);





#endif