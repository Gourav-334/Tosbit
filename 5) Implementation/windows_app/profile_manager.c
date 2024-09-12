/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef PROFILE_MANAGER_C
	#define PROFILE_MANAGER_C



#include "profile_manager.h"










/*____________________________________________________________________________________*/

/*

NOTES!

login_starts()
	check_account_existence()
		password_setting()
			create_account()
				welcome_note()



USED TERMINOLOGIES:

-> Self recursion - Recursion to the same function it is written at.
-> Forward recursion - Recursion to next function as per the procedure.
-> Back recursion - Recursion to previous function in the procedure.



i. buffer[] is used for general storage of anything required.
ii. scanf("%s", str) mustn't be used when SPACES too has to be read.
iii. gets() is UNSAFE and can overwrite memory beyond limit, creating a security issue.
iv. fgets() is safer but adds NEWLINE at end by default & also skips to last fgets() in series.
v. Input buffer must cleaned with flush_stdin() when receiving input character.
vi. Input character must be scanf(" %c", c) to avoid whitespaces & newline hazards.
vii. If username=n, then decrypted password length = 3n + 1.

*/

/*____________________________________________________________________________________*/




















/* If the entered username is in range (in terms of length), then the next function is called */

void login_starts()
{
	while (TRUE)
	{
		if (username_set==TRUE) {break;}



		/* Cleansing username to ensure string doesn't contain garbage values */

		memset(username, 0, USERNAME_MAX_SIZE*sizeof(char));



		/* Console text interface starts! */

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

		printf("Username: "); fgets(username, USERNAME_MAX_SIZE, stdin);
		newline_remover(username);
		


		/* If username size is not in range (self recursion) */

		if ((strlen(username)<USERNAME_MIN_SIZE)||(strlen(username)>USERNAME_MAX_SIZE))
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

			printf("Username must be between 3 to 32 characters!\n\n");

			continue;
		}



		/* If username size is in range (forward recursion) */

		else {check_account_existence();}



		/* Colour back to white & file pointer closing! */

		fclose(fptr);

		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}




















/* Check if the account as per entered username exists or not & follow procedures accordingly */

void check_account_existence()
{
	/* Cleansing buffer */

	memset(buffer, 0, BUFFER_SIZE*sizeof(char));

	snprintf(buffer, sizeof(buffer), "users\\%s.tosbit", username);

	fptr = fopen(buffer, "r");



	/* If username doesn't exist */

	if (fptr==NULL)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

		printf("Username doesn't exist!\n\n");


		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

		printf("Want to open a new account? (y/n): ");
		scanf(" %c", &decision); flush_stdin();



		/* If user wills to create a new account (forward recursion) */

		if (decision=='y')
		{
			memset(buffer, 0, BUFFER_SIZE*sizeof(char));
			strappend(buffer, "users\\");
			strappend(buffer, username);
			newline_remover(username);
			strappend(buffer, ".tosbit");
			memset((buffer + strlen(buffer)), 0, ((BUFFER_SIZE-strlen(buffer)))*sizeof(char));

			username_set = TRUE;

			password_setting();
		}



		/* If user doesn't want to create a new account (back recursion) */

		else if (decision=='n') {login_starts();}



		/* If command other than 'y' and 'n' is entered */

		else
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

			printf("Unknown command received!\n\n");
			login_starts();
		}
	}



	/* If account already exists */

	else {username_set = TRUE; logging_in();}
}




















/* Set & re-authenticate the password, concurrently checking constraints also */

void password_setting()
{
	while (TRUE)
	{
		if (password_set==TRUE) {break;}



		/* Cleansing password & authentication password */

		memset(password, 0, PASSWORD_MAX_SIZE*sizeof(char));
		memset(re_password, 0, PASSWORD_MAX_SIZE*sizeof(char));

		

		/* Password & re-authentication */

		printf("Enter password: "); fgets(password, PASSWORD_MAX_SIZE, stdin);
		memset((password + strlen(password)), 0, (PASSWORD_MAX_SIZE-strlen(password))*sizeof(char));



		/* If password is too short or too long (self recursion) */

		if ((strlen(password)<PASSWORD_MIN_SIZE)||(strlen(password)>PASSWORD_MAX_SIZE))
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

			printf("Password range must be min 6 to 30 characters max!\n\n");

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

			continue;
		}

		

		/* If password is in range (forward recursion) */

		else
		{
			printf("Re-enter password: "); fgets(re_password, PASSWORD_MAX_SIZE, stdin);
			memset(re_password + strlen(re_password), 0, (PASSWORD_MAX_SIZE-(strlen(re_password)))*sizeof(char));

			password_set = TRUE;

			create_account();
		}
	}
}




















/* Acknowledge the re-authentication result to the user */

void create_account()
{
	/* If re-authentication is successful */

	if (!strcmp(password, re_password))
	{
		fptr = fopen(buffer, "w");
		fputs(encrypt(password), fptr);
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

		printf("Account created successfully!\n\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);

		welcome_note();
	}



	/* If re-authentication fails (back recursion) */

	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

		printf("Authentication failed, retry!\n\n");

		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		password_set = FALSE; password_setting();
	}
}




















/* Checking the user's entered password with encrypted code stored locally */

void logging_in()
{
	printf("Password: "); fgets(password, PASSWORD_MAX_SIZE, stdin);
	newline_remover(password);

	memset(username_buffer, 0, USERNAME_BUFFER*sizeof(char));
	fgets(username_buffer, USERNAME_BUFFER, fptr); printf("%c", '\n');



	/* If password matches */

	if (!strcmp(password,decrypt(username_buffer)))
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

		welcome_note();
	}



	/* If the password doesn't match */

	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

		printf("Password doesn't match, retry!\n\n");

		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

		logging_in();
	}
}




















/* Decorative note about license & database system in general */

void welcome_note()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	printf("Hello %s! Welcome to Data-Godown v1.0.0!\n", username);
	printf("Copyright (C) under Apache 2.0 license,");
	printf("read documentation for more information.\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	return;
}



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */