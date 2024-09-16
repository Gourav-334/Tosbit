/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H



#define FALSE 0
#define TRUE 1

#define COMMAND_MAX_LENGTH 257
#define STRING_MAX_LENGTH 33





#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "utility_box.c"
#include "console_colour.c"
#include "data_structures.c"





/* VARIABLES */

char command[COMMAND_MAX_LENGTH];

int state = 0;
int brk = FALSE;





/* FUNCTIONS */

void syntax_parser(char username[]);





#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */