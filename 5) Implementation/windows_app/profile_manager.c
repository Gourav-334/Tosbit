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










/*

BUGS:

i) An endline character is added at the end of any string that has used fgets() function.
ii) Using decrypt() prints the decrypted string twice despite there being no printf() function
used in decrypt().
iii) Same decrypt issue continues, appending everything.



FIXES:

i) That's how it works. If wanting to get rid of it, use newline_remover() function.
ii) Re-check for presence of printf() function, note that strlen() still returns the right value.
iii) decrypt() & encrypt() work as saved strings, flush them with memset to null it.

*/










void profile_manager()
{
	while (exit_status==FALSE)
	{
		switch (functionID)
		{










			/* Check account's existence */

			case 1:

				fptr = fopen("data\\user.tosbit", "r");


				/* If compulsory user system file not found */

				if (fptr==NULL)
				{
					red_console();
					printf("User file not found! Please try re-downloading the package!\n\n");
					white_console();
				}



				/* If compulsory user system file found */

				else
				{
					fgets(buffer, BUFFER_SIZE, fptr);



					/* No user profile set */

					if (strlen(buffer)==0)
					{
						/* Open file in write mode if it doesn't exist */

						fptr = fopen("data\\user.tosbit", "w");
						functionID = 2; continue;
					}



					/* User profile exists */

					else
					{
						yellow_console(); printf("Enter password: "); white_console();
						fgets(password, PASSWORD_MAX_SIZE, stdin); newline_remover(password);


						if (!strcmp(password, decrypt(buffer)))
						{
							memset(buffer, 0 , strlen(buffer)*sizeof(char));
							memset(decrypt(buffer), 0, strlen(decrypt(buffer))*sizeof(char));

							functionID = 4;
						}


						else // CONTINUE FROM HERE 1/2...
						{
							if (strlen(password)<=PASSWORD_MAX_SIZE)
							{
								red_console();
								printf("Password doesn't match!\n\n");
								yellow_console();
							}

							else if (strlen(password)>PASSWORD_MAX_SIZE)
							{
								red_console();
								printf("Password length can be 32 characters max!\n\n");
								yellow_console();
							}

							memset(buffer, 0 , strlen(buffer)*sizeof(char));
							memset(decrypt(buffer), 0, strlen(decrypt(buffer))*sizeof(char));

							continue;
						}
					}
				}



				break;










			/* Create an account */

			case 2:

				yellow_console();
				printf("New username: "); fgets(username, USERNAME_MAX_SIZE, stdin);


				if (strlen(username)>32)
				{
					memset(username, 0, strlen(username)*sizeof(char));
					red_console(); printf("Username must be of 32 characters max!\n\n");
				}


				else if (strlen(username)<USERNAME_MIN_SIZE)
				{
					memset(username, 0, strlen(username)*sizeof(char));
					red_console(); printf("Username must be of minimum 6 characters!\n\n");
				}


				else
				{
					green_console(); printf("Alright!\n\n");
					functionID = 3; continue;
				}



				break;









			/* Set password for created account */

			case 3:	// CONTINUE FROM HERE 2/2...

				memset(password, 0, strlen(password)*sizeof(char));
				memset(re_password, 0, strlen(re_password)*sizeof(char));

				yellow_console();
				printf("Enter password: "); white_console();
				fgets(password, PASSWORD_MAX_SIZE, stdin);

				yellow_console();
				printf("Re-enter password: "); white_console();
				fgets(re_password, PASSWORD_MAX_SIZE, stdin);



				if (!strcmp(password, re_password))
				{
					fputs(encrypt(password), fptr);

					functionID = 4;
				}



				else if (strcmp(password, re_password))
				{
					red_console();
					printf("Passwords don't match, try again!\n\n");
				}



				memset(password, 0, strlen(password)*sizeof(char));
				memset(re_password, 0, strlen(re_password)*sizeof(char));

				continue;



				break;










			/* Welcome message */

			case 4:

				green_console();

				printf("\n\nHello %s! Welcome to Data-Godown v1.0.0!\n", username);
				printf("Copyright (C) under Apache 2.0 license, ");
				printf("read documentation for more information.\n\n");

				white_console();

				exit_status = TRUE;



				break;
		}



		if (exit_status==TRUE) {exit_status==FALSE; break;}
	}
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */