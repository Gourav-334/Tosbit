/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H



#define FALSE 0
#define TRUE 1





#include <stdio.h>
#include <string.h>

#include "utility_box.c"
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










/* Functions */

extern void syntaxParser(char username[]);
extern void attributeParser();










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */