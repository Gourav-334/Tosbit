/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H



#define COMMAND_LENGTH 256
#define STRING_MAX_LENGTH 33
#define MAX_STRINGS 9
#define TOKEN_MAX_SIZE 33
#define TOTAL_DIVIDERS 9



#include "utility_box.c"





/* VARIABLES */

/* Characters */
char dividers[TOTAL_DIVIDERS] = {'.',',',';','[',']','<','=','>'};



/* Arrays */

char command_buffer[STRING_MAX_LENGTH][MAX_STRINGS];



/* Functions */

void string_tokenizer(char command[COMMAND_LENGTH]);





#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */