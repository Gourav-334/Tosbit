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
#include <windows.h>

#include "encrypter.c"
#include "console_colour.h"









/*

NOTES:

*/









/* Variables */

char username[USERNAME_MAX_SIZE];
char password[PASSWORD_MAX_SIZE];
char re_password[PASSWORD_MAX_SIZE];
char file_buff[BUFFER_SIZE];

int functionID = 1;
int exit_status = TRUE;

FILE *fptr;









/* Functions */

void check_account();
void create_account();
void set_password();
void welcome_note();



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */