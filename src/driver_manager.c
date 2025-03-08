#include "../include/driver_manager.h"










/* Variables */

char *hostIP = "@#$";
char hostName[HOSTNAME_MAX_LENGTH] = {0};
char hostPassword[HOSTPASSWORD_MAX_LENGTH] = {0};










/* Connects to the database. */

void setConnection(char *hostIP, char username[], char password[])
{
	/* Declarations */

	FILE *fd;	



	/* Checking if the username exists. */

	fd = fopen("users/user.tosbit", "r");

	if (fd==NULL) {printf("ERROR: Can't find user credential file!\n", username); return;}
	else
	{
		printf("STAT: Checking password for host \"%s\"...\n", hostName);
	}



	/* Checking if password is right. */

	fread(buffer, sizeof(char), sizeof(buffer), fd);
	newline_remover(buffer);

	if (strcmp(password,buffer)) {printf("ERROR: Host %s's password doesn't match!\n", hostName); return;}
	else if (!strcmp(password,buffer)) {strcpy(hostPassword,password); printf("OK: Connected to host %s successfully!\n\n", hostName);}



	/* Connecting to host's IP address. */
}





/* Interprets a passed command. */

void interpret(char *user_cmd)
{syntaxParser(hostName, user_cmd);/////////////////////////////////////////////////////////
	// if (strlen(hostName)==0 || strlen(hostPassword)==0) {printf("ERROR: No host connected!\n");}
	// else {syntaxParser(hostName, user_cmd);}
}