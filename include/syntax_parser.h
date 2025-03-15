/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H





#define FALSE 	0  		// Macro to imitate boolean FALSE behaviour.
#define TRUE 	1		// Macro to imitate boolean TRUE behaviour.





#include <time.h>

#include "utility_box.h"				// Custom utility functions header.
#include "encrypter.h"					// Encryption & decryption header.
#include "database_operations.h"		// Header to run various operations on database.
#include "shell_piping.h"				// Piped output giving header.










/*

-> Majority of macros, strings & pointers have migrated to "database_operations.h".
-> Reason for migration was using less parameters in DB functions without creating a deadlock.
-> Export graph has a linear structure.
-> Graph: database_operations.h >>> database_operations.c >>> syntax_parser.h >>> syntax_parser.c

-> Firstly, the syntaxes are written using Regular Expressions of the database query grammar.
-> Then they are plotted as Deterministic Finite Automata (see in "docs/charts/").
-> Because operations are done on memory & disk while using DFA, it seems like Pushdown Automata.
-> Lastly, the algorithms are written the way a Turing Machine works & then implemented in code.

*/










/* Functions */

extern void syntaxParser(				// Entry function to primary Deterministic Finite Automata.
	char username[],
	char *user_cmd,
	int serverConn
);
extern void attributeParser();			// Parses the attribute(s) passed for making a table.










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */