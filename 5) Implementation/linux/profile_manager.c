/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



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
iv) When input string exceeds its buffer size, the string is read in sets of strings. For example,
if entered string is of 74 chars & buffer size is 32 chars, then it will be read in set {32, 32, 10}.



FIXES:

i) That's how it works. If wanting to get rid of it, use newline_remover() function.
ii) Re-check for presence of printf() function, note that strlen() still returns the right value.
iii) decrypt() & encrypt() work as saved strings, flush them with memset to null it.
iv) The so called race condition can be simply solved by using memset() for fgets().

*/










/* Variables */

char username[USERNAME_MAX_SIZE] = {0};
char password[PASSWORD_MAX_SIZE] = {0};
char re_password[PASSWORD_MAX_SIZE] = {0};
char buff[BUFFER_SIZE] = {0};

int functionID = -1;			// Might become troubling later on.
int exit_status = -1;

FILE *file = NULL;










void profile_manager()
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
