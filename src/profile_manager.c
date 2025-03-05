/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"
#include "../include/utility_box.h"










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










/* Main function for user login. */

int profileManager()
{
	/* Declarations */

	char c;
	int success;


	/* Opening 'users.tosbit' with NULL safety. */

	file = fopen("users/user.tosbit", "r+");


	/* If 'user.tosbit' wasn't found. */

	if (file==NULL)
	{
		printf("WARN: Your Tosbit pacakge wasn't probably downloaded/installed properly.\n");
		printf("WARN: Some files are missing from the source directory, make sure nothing was misplaced.\n\n");

		file = fopen("users/user.tosbit", "w");
	}


	/* If 'user.tosbit' exists, but its empty inside. */

	if (file!=NULL && reachedEOF(file))
	{
		printf("Enter new username: "); fgets(username, sizeof(username), stdin); newline_remover(username);
		printf("Enter password: "); fgets(password, sizeof(password), stdin); newline_remover(password);
		printf("Re-enter password: "); fgets(re_password, sizeof(re_password), stdin); newline_remover(re_password);

		if (strcmp(password,re_password)) {printf("ERROR: Your passwords don't match, please restart the engine.\n"); success = FALSE;}
		else if (!strcmp(password,re_password))
		{
			fputs(encrypt(username), file); fputc('\n', file); 
			memset(encrypt(username), 0, sizeof(encrypt(username))); fputs(encrypt(password), file);

			printf("Hi %s!\n\n", username);

			success = TRUE;
		}
	}


	/* If user profile has already been made. */

	else if (file!=NULL && !reachedEOF(file))
	{
		c = fgetc(file);
		while (c!='\n') {username[strlen(username)] = c; c = fgetc(file);}

		fgets(buff, sizeof(buff), file); strcpy(re_password, decrypt(buff)); newline_remover(re_password);
		printf("Enter password: "); fgets(password, sizeof(password), stdin); newline_remover(password);
printf("username: %s, password: %s\n", decrypt(username), password);
		if (strcmp(password,re_password)) {printf("ERROR: What you entered doesn't match the password!\n"); success = FALSE;}
		else if (!strcmp(password,re_password)) {printf("\n*** Tosbit v0.1.0-beta ***\n"); printf("Welcome back %s!\n\n", decrypt(username)); success = TRUE;}
	}



	/* Safely closing file. */

	fclose(file);


	/* Returning success status. */

	return success;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */
