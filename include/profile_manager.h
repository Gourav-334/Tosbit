/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef PROFILE_MANAGER_H
	#define PROFILE_MANAGER_H





/* Constant (must not change) macros */

#define TRUE 	1  			// Macro to imitate boolean TRUE behaviour.
#define FALSE 	0			// Macro to imitate boolean FALSE behaviour.


#define USERNAME_MIN_SIZE 	4  			// Minimum allowed length for username.
#define USERNAME_MAX_SIZE 	33  		// Maximum allowed length for username.
#define BUFFER_SIZE 		133  		// Size of buffer allowed.
#define PASSWORD_MIN_SIZE 	7  			// Minimum allowed length for password.
#define PASSWORD_MAX_SIZE 	33  		// Maximum allowed length for password.





/* Header & source file inclusion */

#include <stdlib.h>				// Standard library functionalities header.
#include <unistd.h>				// UNIX standard library.
#include <termios.h>			// Disabling ECHO to hide password.

#include "encrypter.h"			// Encryption & decryption header.
#include "utility_box.h"  		// Custom utility functions header.










/* Variables */

extern char username 		[USERNAME_MAX_SIZE];		// Stores username for the user.
extern char codedUsername 	[MAX_ENCRYPTED_SIZE];		// Stores encrypted username in it.
extern char password 		[PASSWORD_MAX_SIZE];		// Stores password for the user.
extern char codedPassword 	[MAX_ENCRYPTED_SIZE];		// Stores encrypted password in it.










/* Functions */

extern int profileManager();		// Handles the user credentials & verification etc.










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */