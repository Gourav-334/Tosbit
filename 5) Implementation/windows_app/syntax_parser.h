/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H



#define FALSE 0
#define TRUE 1

#define COMMAND_MAX_LENGTH 257
#define STRING_MAX_LENGTH 33
#define DATABASE_MAX_LENGTH 33
#define TABLE_MAX_LENGTH 33
#define DIRECTORY_MAX_LENGTH 65
#define BUFFER_MAX_LENGTH 133





#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "utility_box.c"
#include "console_colour.c"
#include "data_structures.c"
#include "encrypter.c"





/* VARIABLES */

char filechar = '$';
char prev_filechar = '$';

char command[COMMAND_MAX_LENGTH];
char database[DATABASE_MAX_LENGTH];
char table[TABLE_MAX_LENGTH];
char directory[DIRECTORY_MAX_LENGTH];
char buffer[BUFFER_MAX_LENGTH];

int state = 0;
int zero_count = 0;

int brk = FALSE;
int db_found = FALSE;

FILE *fptr;





/* FUNCTIONS */

void syntax_parser(char username[]);





#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */