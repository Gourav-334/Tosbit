/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef PROFILE_MANAGER_C
	#define PROFILE_MANAGER_C



#include "profile_manager.h"










/*

Total continuation points: 2


functionIDs:

Check account = 1
Create account = 2
Set password = 3
Welcome note = 4

*/










void profile_manager()
{
	while (exit_status==TRUE)
	{
		switch (functionID)
		{










			/* Check account's existence */

			case 1:

				fptr = fopen("data\\user.tosbit", "r");


				if (fptr==NULL)
				{
					red_console();
					printf("User file not found! Please try re-downloading the package!\n\n");
					white_console();
				}


				else
				{
					fgets(buffer, BUFFER_SIZE, fptr);

					if (strlen(buffer)==0) {functionID = 2; continue;}

					else
					{
						yellow_console(); printf("Enter password: ");
						fgets(password, PASSWORD_MAX_SIZE, stdin);

						// CONTINUE FROM HERE 2/2 //////////////////////////////////////
					}
				}



				break;










			/* Create an account */

			case 2:

				yellow_console();
				printf("New username: "); fgets(username, USERNAME_MAX_SIZE, stdin);


				if (strlen(username)>32)
				{
					memset(username, 0, USERNAME_MAX_SIZE);
					red_console(); printf("Username must be of 32 characters max!\n\n");
				}


				else if (strlen(username)<USERNAME_MIN_SIZE)
				{
					memset(username, 0, USERNAME_MAX_SIZE);
					red_console(); printf("Username must be of minimum 6 characters!\n\n");
				}


				else
				{
					green_console(); printf("Alright!\n\n");
					functionID = 3; continue;
				}



				break;









			/* Set password for created account */

			case 3:

				yellow_console();

				memset(password, 0, strlen(password)*sizeof(char));
				memset(re_password, 0, strlen(re_password)*sizeof(char));

				printf("Enter password: "); fgets(password, PASSWORD_MAX_SIZE, stdin);
				printf("Re-enter password: "); fgets(re_password, PASSWORD_MAX_SIZE, stdin);



				if (!strcmp(password, re_password)) {functionID = 4; continue;}

				else if (strcmp(password, re_password))
				{
					red_console();
					printf("Passwords don't match, try again!\n\n");

					continue;
				}



				break;










			/* Welcome message */

			case 4:

				blue_console();

				printf("Hello %s! Welcome to Data-Godown v1.0.0!\n", username);
				printf("Copyright (C) under Apache 2.0 license,");
				printf("read documentation for more information.\n\n");



				break;
		}



		if (exit_status==FALSE) {exit_status==TRUE; break;}
	}
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */