#ifndef DRIVER_MANAGER
	#define DRIVER_MANAGER

#define HOSTNAME_MAX_LENGTH 33
#define HOSTPASSWORD_MAX_LENGTH 33

#define TRUE 1
#define FALSE 0



#include <errno.h>

#include "encrypter.h"
#include "utility_box.h"
#include "client.h"
#include "syntax_parser.h"





/* Declarations */

extern int connected;





/* Functions */

extern void setConnection(
	char username[],
	char password[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[]
);
extern void interpret(char *user_cmd);





#endif