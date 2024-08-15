#ifndef PROFILE_MANAGER_H
	#define PROFILE_MANAGER_H





#define USERNAME_MIN_SIZE 3
#define USERNAME_MAX_SIZE 33

#define USERNAME_BUFFER 101
#define BUFFER_SIZE 39

#define PASSWORD_MIN_SIZE 6
#define PASSWORD_MAX_SIZE 33

#define TRUE 1
#define FALSE 0





#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "encrypter.c"









/* GLOBAL VARIABLES */

// boolean(s)
int login_complete = FALSE;
int username_set = FALSE;
int password_set = FALSE;

// char(s)
char decision;

// string(s)
char username[USERNAME_MAX_SIZE] = {0};
char username_buffer[USERNAME_BUFFER] = {0};
char buffer[BUFFER_SIZE] = {0}; 
char password[PASSWORD_MAX_SIZE] = {0};
char re_password[PASSWORD_MAX_SIZE] = {0};

// pointer(s)
FILE *fptr = NULL;





void login_starts();
void check_account_existence();
void password_setting();
void create_account();
void logging_in();
void welcome_note();



#endif