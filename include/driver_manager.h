#ifndef DRIVER_MANAGER
	#define DRIVER_MANAGER

#define HOSTNAME_MAX_LENGTH 33
#define HOSTPASSWORD_MAX_LENGTH 33



#include "encrypter.h"
#include "client.h"
#include "utility_box.h"





/* Variables */

extern char *hostIP;
extern char hostName[HOSTNAME_MAX_LENGTH];
extern char hostPassword[HOSTPASSWORD_MAX_LENGTH];





/* Functions */

extern void setConnection(char *hostIP, char hostName[], char hostPassword[]);
extern void interpret(char *user_cmd);





#endif