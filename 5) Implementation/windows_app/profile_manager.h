/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef PROFILE_MANAGER_H
	#define PROFILE_MANAGER_H





/* Constant (must not change) macros */

#define USERNAME_MIN_SIZE 3
#define USERNAME_MAX_SIZE 33

#define USERNAME_BUFFER 101
#define BUFFER_SIZE 39

#define PASSWORD_MIN_SIZE 6
#define PASSWORD_MAX_SIZE 33

#define TRUE 1
#define FALSE 0





/* Header & source file inclusion */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "encrypter.c"









// GLOBAL VARIABLES

/* Global boolean variables*/

int login_complete = FALSE;
int username_set = FALSE;
int password_set = FALSE;



/* Characters */

char decision;



/* Strings */

char username[USERNAME_MAX_SIZE] = {0};
char username_buffer[USERNAME_BUFFER] = {0};
char buffer[BUFFER_SIZE] = {0}; 
char password[PASSWORD_MAX_SIZE] = {0};
char re_password[PASSWORD_MAX_SIZE] = {0};


/* Pointers */

FILE *fptr = NULL;





/* Login functions declaration */

void login_starts();
void check_account_existence();
void password_setting();
void create_account();
void logging_in();
void welcome_note();



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */