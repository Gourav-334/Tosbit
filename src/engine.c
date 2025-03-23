/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include <termios.h>		// Disabling ECHO to hide password.
#include <unistd.h>			// UNIX standard header.

#include "../include/profile_manager.h"
#include "../include/driver_manager.h"
#include "../include/shell_piping.h"
#include "../include/utility_box.h"


#define TRUE 1
#define FALSE 0










/* The main windows for engine. */

int main(int argc, char **argv[])
{
	/* Declarations */

	char decision;
	char hostIP[16] = {0};
	short unsigned int port;

	char hostUsername[MAX_DECRYPTED_SIZE] = {0};
	char hostPassword[MAX_DECRYPTED_SIZE] = {0};


	/* Structures */

	struct termios oldt, newt;



	/* If username exists. */

	if (profileManager()==TRUE)
	{
		/* Asking user for connecting to certain server. */

		printf("Do you want to access an external server? (y/n): "); scanf("%c", &decision); getchar();


		if (decision=='y'||decision=='Y')
		{
			/* Getting server information. */

			printf("Enter host IP: "); fgets(hostIP, sizeof(hostIP), stdin); newline_remover(hostIP);
			printf("Enter port number: "); scanf("%hu", &port); getchar();	// Consuming '\n' in buffer.
			printf("Enter host username: "); fgets(hostUsername, sizeof(hostUsername), stdin); newline_remover(hostUsername);

			printf("Enter host password: "); 
			tcgetattr(STDIN_FILENO, &oldt); newt = oldt;		// Disabling reading password.
	    	newt.c_lflag &= ~ECHO; tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	    	fgets(hostPassword, sizeof(hostPassword), stdin); newline_remover(hostPassword);
	    	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);			// Re-enabling reading terminal.


			printf("\n\n");



			/* Connecting to driver. */

			printf("STAT: Accessing server-side file system...\n");

			setConnection(
				decrypt(codedUsername), decrypt(codedPassword),
				hostIP, port, hostUsername, hostPassword, TRUE
			);

			endConnection();
		}
		else if (decision=='n'||decision=='N')
		{
			printf("STAT: Accessing client-side file-system...\n\n");
			syntaxParser(username, NULL, FALSE);
		}
		else
		{
			printf("STAT: Unkown decision passed, accessing client data as default.\n\n");
			syntaxParser(username, NULL, FALSE);
		}
	}



	return 0;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */