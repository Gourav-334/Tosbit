/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"










/*

Total continuation points: 2


functionIDs:

Check account = 1
Create account = 2
Set password = 3
Welcome note = 4

*/










/* Variables */

char username[USERNAME_MAX_SIZE] = {0};
char password[PASSWORD_MAX_SIZE] = {0};
char re_password[PASSWORD_MAX_SIZE] = {0};
char buff[BUFFER_SIZE] = {0};

int functionID = 1;
int exit_status = FALSE;

FILE *file = NULL;










void profileManager()
{
	while (exit_status==FALSE)
	{
		switch (functionID)
		{










			/* Check account's existence */

			case 1:

				file = fopen("data/user.tosbit", "r");


				/* If compulsory user system file not found */

				if (file==NULL)
				{
					printf("Error: User file not found! Please try re-downloading the package!\n\n");
				}



				/* If compulsory user system file found */

				else
				{
					fgets(buff, BUFFER_SIZE, file);



					/* No user profile set */

					if (strlen(buff)==0)
					{
						/* Open file in write mode if it doesn't exist */

						file = fopen("data/user.tosbit", "w");
						functionID = 2; continue;
					}



					/* User profile exists */

					else
					{
						printf("Enter password: ");
						fgets(password, PASSWORD_MAX_SIZE, stdin); newline_remover(password);



						if (strlen(password)>(PASSWORD_MAX_SIZE-2))
						{
							printf("Error: Password size must not exceed %d characters!\n\n", PASSWORD_MAX_SIZE);
							
							memset(fgets(password, PASSWORD_MAX_SIZE, stdin), 0, strlen(password)*sizeof(char));
						}



						else if (strlen(password)<PASSWORD_MIN_SIZE)
						{
							printf("Error: Password size must be more than %d characters!\n\n", PASSWORD_MIN_SIZE);
						}



						else
						{
							if (!strcmp(password, decrypt(buff)))
							{
								memset(buff, 0 , strlen(buff)*sizeof(char));
								memset(decrypt(buff), 0, strlen(decrypt(buff))*sizeof(char));

								functionID = 4;
							}


							else if (strcmp(password, decrypt(buff)))
							{
								printf("Error: Password doesn't match!\n\n");
							}
						}



						memset(buff, 0 , strlen(buff)*sizeof(char));
						memset(decrypt(buff), 0, strlen(decrypt(buff))*sizeof(char));

						continue;
					}
				}



				break;










			/* Create an account */

			case 2:

				printf("New username: "); fgets(username, USERNAME_MAX_SIZE, stdin);



				if (strlen(username)>(USERNAME_MAX_SIZE-2))
				{
					memset(username, 0, strlen(username)*sizeof(char));
					printf("Username must be of %d characters max!\n\n", USERNAME_MAX_SIZE);
					memset(fgets(username, USERNAME_MAX_SIZE, stdin), 0, strlen(username)*sizeof(char));
				}



				else if (strlen(username)<(USERNAME_MIN_SIZE+1))
				{
					memset(username, 0, strlen(username)*sizeof(char));
					printf("Error: Username must be of minimum %d characters!\n\n", USERNAME_MIN_SIZE);
				}


				else {printf("OK: Alright!\n\n"); functionID = 3;}


				continue;



				break;









			/* Set password for created account */

			case 3:

				memset(password, 0, strlen(password)*sizeof(char));
				memset(re_password, 0, strlen(re_password)*sizeof(char));

				printf("Enter password: ");
				fgets(password, PASSWORD_MAX_SIZE, stdin);



				if (strlen(password)>(PASSWORD_MAX_SIZE-2))
				{
					printf("Error: Password size must not exceed %d characters!\n\n", PASSWORD_MAX_SIZE);
					memset(fgets(password, PASSWORD_MAX_SIZE, stdin), 0, strlen(password)*sizeof(char));
				}



				else if (strlen(password)<PASSWORD_MIN_SIZE)
				{
					printf("Error: Password size must be more than %d characters!\n\n", PASSWORD_MIN_SIZE);
				}



				else
				{
					printf("Re-enter password: ");
					fgets(re_password, PASSWORD_MAX_SIZE, stdin);

					if (!strcmp(password, re_password))
					{
						fputs(encrypt(password), file);
						memset(encrypt(password), 0, strlen(password)*sizeof(char));

						fputs(encrypt(username), file);
						memset(encrypt(username), 0, strlen(username)*sizeof(char));

						functionID = 4;
					}


					else if (strcmp(password, re_password))
					{
						printf("Error: Passwords don't match, try again!\n\n");
					}
				}



				memset(password, 0, strlen(password)*sizeof(char));
				memset(re_password, 0, strlen(re_password)*sizeof(char));

				continue;



				break;










			/* Welcome message */

			case 4:

				printf("\n\nHello %s! Welcome to Data-Godown v1.0.0!\n", username);
				printf("Copyright (C) under Apache 2.0 license, ");
				printf("read documentation for more information.\n\n");

				exit_status = TRUE;



				break;
		}



		if (exit_status==TRUE) {exit_status==FALSE; break;}
	}
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */
