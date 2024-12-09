/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H



#define FALSE 0
#define TRUE 1

#define STRING_MAX_LENGTH 33





#include <stdio.h>
#include <string.h>

#include "utility_box.c"
#include "console_colour.c"
#include "data_structures.c"
#include "encrypter.c"
#include "transition_tool.c"
#include "database_operations.c"










/*

-> Majority of macros, strings & pointers have migrated to "database_operations.h".
-> Reason for migration was using less parameters in DB functions without creating a deadlock.
-> Export graph has a linear structure.
-> Graph: database_operations.h >>> database_operations.c >>> syntax_parser.h >>> syntax_parser.c

-> Firstly, the syntaxes are written using regular expressions of the database query grammar.
-> Then they are plotted as Deterministic Finite Automata [see in "6) Flowcharts/"].
-> Lastly, the algorithms are written the way a Turing Machine works & then implemented in code.

*/










/* Variables */

char filechar = '$';
char prev_filechar = '$';

int state = 0;
int zero_count = 0;

int brk = FALSE;			// Set TRUE when the syntax goes wrong
int db_found = FALSE;







/* Functions */

void syntax_parser(char username[]);










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */