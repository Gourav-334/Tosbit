/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"










/* Variables */

char username[USERNAME_MAX_SIZE] = {0};
char codedUsername[MAX_ENCRYPTED_SIZE] = {0};
char password[PASSWORD_MAX_SIZE] = {0};
char codedPassword[MAX_ENCRYPTED_SIZE] = {0};
char re_password[PASSWORD_MAX_SIZE] = {0};










/* Main function for user login. */

int profileManager()
{
	/* Declarations */

	FILE *file = NULL;
	char c;


	/* Structures */

	struct termios oldt, newt;


	/* Opening 'users.tosbit' with NULL safety. */

	file = fopen("users/user.tosbit", "r+");



	/* If 'user.tosbit' wasn't found. */

	if (file==NULL)
	{
		printf("WARN: Your Tosbit pacakge wasn't probably downloaded/installed properly.\n");
		printf("WARN: Some files are missing from the source directory, make sure nothing was misplaced.\n");


		/* Creating the missing file. */

		file = fopen("users/user.tosbit", "w");
		printf("WARN: A change is applied, please restart the engine.\n");


		return FALSE;
	}



	/* If 'user.tosbit' exists, but its empty inside. */

	if (file!=NULL && reachedEOF(file))
	{
		/* Sign-up for new user. */

		printf("Enter new username: "); fgets(username, sizeof(username), stdin); newline_remover(username);

		if (strlen(username)<(USERNAME_MIN_SIZE-1))
			{printf("ERROR: The username must be at least %d characters long!\n", USERNAME_MIN_SIZE-1); return FALSE;}

		else if (strlen(username)>(USERNAME_MAX_SIZE-1))
			{printf("ERROR: The password must be at least %d characters long!\n", USERNAME_MAX_SIZE-1); return FALSE;}


		/* Continuing with password. */

		printf("Enter password: ");

	    tcgetattr(STDIN_FILENO, &oldt); newt = oldt;		// Disabling reading password.
	    newt.c_lflag &= ~ECHO; tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	    
		fgets(password, sizeof(password), stdin); newline_remover(password);
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);			// Re-enabling reading terminal.
		printf("\n");


		if (strlen(password)<(PASSWORD_MIN_SIZE-1))
			{printf("ERROR: The password must be at least %d characters long!\n", PASSWORD_MIN_SIZE-1); return FALSE;}

		else if (strlen(password)>=(PASSWORD_MAX_SIZE-1))
			{printf("ERROR: The password must be at least %d characters long!\n", PASSWORD_MAX_SIZE-1); return FALSE;}


		printf("Re-enter password: ");

		tcgetattr(STDIN_FILENO, &oldt); newt = oldt;		// Disabling reading password.
	    newt.c_lflag &= ~ECHO; tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	    fgets(re_password, sizeof(re_password), stdin); newline_remover(re_password);
	    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);			// Re-enabling reading terminal.
	    printf("\n");


		/* Matching passwords. */

		if (strcmp(password,re_password)) {printf("ERROR: Your passwords don't match, please restart the engine.\n"); return FALSE;}
		else if (!strcmp(password,re_password))
		{
			fputs(encrypt(username), file); fputc('\n', file); 
			memset(encrypt(username), 0, sizeof(encrypt(username))); fputs(encrypt(password), file);

			printf("Hi %s!\n\n", username);
		}
	}



	/* If user profile has already been made. */

	else if (file!=NULL && !reachedEOF(file))
	{
		/* Storing the encrypted username. */

		c = fgetc(file);
		while (c!='\n') {codedUsername[strlen(codedUsername)] = c; c = fgetc(file);}


		/* Storing remaining bytes (encrypted password). */

		fgets(codedPassword, sizeof(codedPassword), file); strcpy(re_password, decrypt(codedPassword)); newline_remover(re_password);
		printf("Enter password: "); fgets(password, sizeof(password), stdin); newline_remover(password);


		/* Greeting users or exiting program for wrong credentials. */

		if (strcmp(password,re_password)) {printf("ERROR: What you entered doesn't match the password!\n"); return FALSE;}
		else if (!strcmp(password,re_password)) {printf("\n***** Tosbit v0.1.0-beta *****\n\n"); printf("Welcome back %s!\n\n", decrypt(codedUsername));}
	}



	/* Safely closing file. */

	fclose(file);


	/* Returning TRUE if it makes to the end of the function (success in login/sign-up). */

	return TRUE;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */