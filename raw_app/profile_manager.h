#ifndef PROFILE_MANAGER_H
	#define PROFILE_MANAGER_H





#define USERNAME_MIN_SIZE 3
#define USERNAME_MAX_SIZE 33

#define USERNAME_BUFFER 101
#define BUFFER_SIZE 39

#define PASSWORD_MIN_SIZE 6
#define PASSWORD_MAX_SIZE 33

#define CONTINUE 1
#define DISCONTINUE 0





#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "encrypter.c"
#include "utility_box.c"





// Function continuation manager.

int login_system_func = CONTINUE;
int check_account_existence_func = CONTINUE;
int password_setting_func = CONTINUE;
int create_account_func = CONTINUE;





/* GLOBAL VARIABLES */

// char(s)
char decision;

// string(s)
char username[USERNAME_MAX_SIZE];
char username_buffer[USERNAME_BUFFER];
char buffer[BUFFER_SIZE]; int buffer_pos = 0;
char password[PASSWORD_MAX_SIZE]; int password_pos = 0;
char re_password[PASSWORD_MAX_SIZE]; int re_password_pos = 0;

// pointer(s)
FILE *fptr;





void login_system();
void check_account_existence();
void password_setting();
void create_account();
void logging_in();



#endif