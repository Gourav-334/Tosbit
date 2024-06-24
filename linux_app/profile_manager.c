#ifndef PROFILE_MANAGER_C
	#define PROFILE_MANAGER_C



#include "profile_manager.h"




















//--------------------------------------------------------------------------------------

/*

Comment sections in series:

		1) Cleansing username.
	2) Console text interface starts!
	3) If username size is not in range (self recursion).
	4) If username size is in range (forward recursion).
	5) Colour back to white & file pointer closing!
	
	6) Cleansing buffer.
	7) If username doesn't exist.
		8) If user wills to create a new account (forward recursion).
		9) If user doesn't want to create a new account (back recursion).
	
	10) Password & re-authentication.
	11) If password is too short or too long (self recursion).
	12) If password is in range (forward recursion).

	13) If re-authentication is successful.
	14) If re-authentication fails (back recursion).

*/


//--------------------------------------------------------------------------------------


/*

NOTES!:

login_starts()
	login_starts()
		check_account_existence()
			password_setting()
				create_account()
					welcome_note()


i. buffer[] is used for general storage of anything required.
ii. scanf("%s", str) mustn't be used when SPACES too has to be read.
iii. gets() is UNSAFE and can overwrite memory beyond limit, creating a security issue.
iv. fgets() is safer but adds NEWLINE at end by default & also skips to last fgets() in series.
v. Both get() and fgets() show apparent RACE CONDITION by passing empty strings by themselves.
vi. If username=n, then decrypted password length = 3n + 1.

*/


//--------------------------------------------------------------------------------------




















void login_starts()
{
	while (TRUE)
	{
		// 1) Cleansing username.

		memset(username, 0, USERNAME_MAX_SIZE*sizeof(char));


		// 2) Console text interface starts!

		printf("Username: "); std::getline(std::cin, input); // RACE CONDITION 1
		newline_remover(username);

		if (strlen(username)==0) {continue;}
		


		// 3) If username size is not in range (self recursion).

		if ((strlen(username)<USERNAME_MIN_SIZE)||(strlen(username)>USERNAME_MAX_SIZE))
		{
			printf("Username must be between 3 to 32 characters!\n\n");

			continue;
		}



		// 4) If username size is in range (forward recursion).

		else {check_account_existence();}



		// 5) Colour back to white & file pointer closing!

		fclose(fptr);
	}
}




















void check_account_existence()
{
	// 6) Cleansing buffer.

	memset(buffer, 0, BUFFER_SIZE*sizeof(char));

	snprintf(buffer, sizeof(buffer), "users\\%s.dgw", username);

	fptr = fopen(buffer, "r");



	// 7) If username doesn't exist.

	if (fptr==NULL)
	{
		printf("Username doesn't exist!\n\n");



		printf("Want to open a new account? (y/n): ");
		scanf("%c", &decision); printf("\n");



		// 8) If user wills to create a new account (forward recursion).

		if (decision=='y')
		{
			memset(buffer, 0, BUFFER_SIZE*sizeof(char));
			strappend(buffer, &buffer_pos, "users\\");
			strappend(buffer, &buffer_pos, username);
			strappend(buffer, &buffer_pos, ".dgw");
			memset((buffer + buffer_pos), 0, (BUFFER_SIZE*sizeof(char) - buffer_pos));

			password_setting();
		}



		// 9) If user doesn't want to create a new account (back recursion).

		else if (decision=='n') {login_starts();}



		// 10) If command other than 'y' and 'n' is entered.

		else
		{
			printf("Unknown command received!");
			login_starts();
		}
	}



	// 11) If account already exists.

	else {logging_in();}
}




















void password_setting()
{
	while (TRUE)
	{
		memset(password, 0, PASSWORD_MAX_SIZE*sizeof(char));
		memset(re_password, 0, PASSWORD_MAX_SIZE*sizeof(char));

		

		// 10) Password & re-authentication.

		printf("Enter password: "); std::getline(std::cin, password); // RACE CONDITION 2
		memset((password + strlen(password)), 0, (PASSWORD_MAX_SIZE-strlen(password)));

		if (strlen(password)==0) {continue;}



		// 11) If password is too short or too long (self recursion).

		if ((strlen(password)<PASSWORD_MIN_SIZE)||(strlen(password)>PASSWORD_MAX_SIZE))
		{
			printf("Password range must be min 6 to 30 characters max!\n\n");

			continue;
		}

		

		// 12) If password is in range (forward recursion).

		else
		{
			printf("Re-enter password: "); std::getline(std::cin, re_password);
			memset(re_password + strlen(re_password), 0, (PASSWORD_MAX_SIZE-(strlen(re_password))));

			create_account();
		}
	}
}




















void create_account()
{
	// 13) If re-authentication is successful.

	if (!strcmp(password, re_password))
	{
		fptr = fopen(buffer, "w");
		fputs(encrypt(password), fptr);

		printf("Account created successfully!\n\n");

		welcome_note();
	}



	// 14) If re-authentication fails (back recursion).

	else
	{
		printf("Authentication failed, retry!\n\n");

		password_setting();
	}
}




















void logging_in()
{
	printf("Password: "); fgets(password, PASSWORD_MAX_SIZE, stdin);
	newline_remover(password);

	fgets(username_buffer, USERNAME_BUFFER, fptr); printf("\n");



	// 12) If password matches.

	if (!strcmp(password,decrypt(username_buffer)))
	{
		welcome_note();
	}



	// 13) If the password doesn't match.

	else
	{
		printf("Password doesn't match, retry!\n\n");

		logging_in();
	}
}




















void welcome_note()
{
	printf("Hello %s! Welcome to Data-Godown v1.0.0!\n", username);
	printf("Copyright (C) under Apache 2.0 license,");
	printf("read documentation for more information.\n\n");

	return;
}



#endif
