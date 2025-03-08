/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"
#include "../include/driver_manager.h"





int main(int argc, char **argv[])
{
	/* Declarations */

	char decision;



	/* If username exists. */

	if (profileManager()==TRUE)
	{
		/* Fetching the location. */

		getLocation();



		/* Asking user for connecting to certain server. */

		printf("Do you want to access an external server? (y/n): "); scanf("%c", &decision);


		if (decision=='y'||decision=='Y')
		{
			printf("STAT: Accessing server-side file system...\n\n");
			setConnection("123.141.138.013", username, "tangible%troops88");
		}
		else if (decision=='n'||decision=='N')
		{
			printf("STAT: Accessing client-side file-system...\n\n");
			syntaxParser(username, NULL);
		}
		else
		{
			printf("STAT: Unkown decision passed, accessing client data as default.\n\n");
			syntaxParser(username, NULL);
		}
	}



	return 0;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */