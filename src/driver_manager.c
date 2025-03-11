#include "../include/driver_manager.h"










/* Variable definitions. */

int connected = FALSE;










/* Connects to the database. */

void setConnection(
	char username[],
	char password[],
	char hostIP[],
	short unsigned int port,
	char hostUsername[],
	char hostPassword[]
)
{
	/* Declarations */

	FILE *fptr;
	char c;

	char codedUsername[MAX_ENCRYPTED_SIZE] = {0};
	char codedPassword[MAX_ENCRYPTED_SIZE] = {0};



	/* Checking if the username exists. */

	fptr = fopen("users/user.tosbit", "r");


	if (fptr==NULL) {printf("ERROR: Can't find user credential file!\n"); return;}
	else
	{
		/* Fetching encrypted username & password. */

		c = fgetc(fptr);
		while (c!='\n') {codedUsername[strlen(codedUsername)] = c; c = fgetc(fptr);}

		c = fgetc(fptr);
		while (!reachedEOF(fptr)) {codedPassword[strlen(codedPassword)] = c; c = fgetc(fptr);}

		fclose(fptr);


		/* Confirming details on terminal screen. */

		if (!strcmp(username,decrypt(codedUsername)) && !strcmp(password,decrypt(codedPassword)))
		{
			printf("STAT: Checking credentials for host %s...\n", hostUsername);
			runClient(username, hostIP, port, hostUsername, hostPassword);
		}
		else {printf("ERROR: Username or password doesn't match!\n"); return;}
	}
}





/* Interprets a passed command. */

void interpret(char *user_cmd)
{
	if (connected==TRUE) {printf("Connected!\n");}
	else if (connected==FALSE) {printf("Not connected!\n");}
}