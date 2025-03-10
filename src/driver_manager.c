#include "../include/driver_manager.h"










/* Variable definitions. */

int connected = FALSE;










/* Connects to the database. */

void setConnection(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[])
{
	/* Declarations */

	FILE *fptr;
	char c;
	char codedUsername[MAX_ENCRYPTED_SIZE] = {0};



	/* Checking if the username exists. */

	fptr = fopen("users/user.tosbit", "r");


	if (fptr==NULL) {printf("ERROR: Can't find user credential file!\n"); return;}
	else
	{
		c = fgetc(fptr);
		while (c!='\n') {codedUsername[strlen(codedUsername)] = c; c = fgetc(fptr);} fclose(fptr);


		/* Confirming details on terminal screen. */

    	printf("Username: %s\n", decrypt(codedUsername));


		if (!strcmp(username,decrypt(codedUsername)))
		{
			printf("STAT: Checking credentials for host %s...\n", hostUsername);
			
			if (runClient(username, hostIP, port, hostUsername, hostPassword)!=EXIT_FAILURE)
				connected = TRUE;
		}
		else {printf("ERROR: Username doesn't match!\n"); return;}
	}
}





/* Interprets a passed command. */

void interpret(char *user_cmd)
{
	if (connected==TRUE) {printf("Connected!\n");}
	else if (connected==FALSE) {printf("Not connected!\n");}
}