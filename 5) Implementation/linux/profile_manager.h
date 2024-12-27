/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef PROFILE_MANAGER_H
	#define PROFILE_MANAGER_H





/* Constant (must not change) macros */

#define USERNAME_MIN_SIZE 3
#define USERNAME_MAX_SIZE 33

#define BUFFER_SIZE 133

#define PASSWORD_MIN_SIZE 6
#define PASSWORD_MAX_SIZE 33

#define TRUE 1
#define FALSE 0





/* Header & source file inclusion */

#include <stdio.h>
#include <stdlib.h>

#include "encrypter.c"










/* Variables */

extern char username[USERNAME_MAX_SIZE];
extern char password[PASSWORD_MAX_SIZE];
extern char re_password[PASSWORD_MAX_SIZE];
extern char buff[BUFFER_SIZE];

extern int functionID;
extern int exit_status;

extern FILE *file;









/* Functions */

extern void profile_manager();



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */