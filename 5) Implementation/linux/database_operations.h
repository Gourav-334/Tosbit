#ifndef DATABASE_OPERATIONS_H
	#define DATABASE_OPERATIONS_H

#define COMMAND_MAX_LENGTH 257
#define DATABASE_MAX_LENGTH 17
#define TABLE_MAX_LENGTH 17
#define DIRECTORY_MAX_LENGTH 129
#define BUFFER_MAX_LENGTH 257

#define DATA_TYPE_MAX_LENGTH 7
#define ATTRIBUTE_MAX_LENGTH 17

#define TRUE 1
#define FALSE 0





#include <stdio.h>
#include <stdlib.h>
#include <string.h>










/* Major buffer string & other variables. */

extern FILE *fptr;

extern char command[COMMAND_MAX_LENGTH];
extern char database[DATABASE_MAX_LENGTH];
extern char table[TABLE_MAX_LENGTH];
extern char directory[DIRECTORY_MAX_LENGTH];
extern char buffer[BUFFER_MAX_LENGTH];
extern char dataType[DATA_TYPE_MAX_LENGTH];
extern char attribute[ATTRIBUTE_MAX_LENGTH];

extern char flusher;

extern int state = 0;							// Main automaton
extern int state2 = 0;							// Table attribute automaton
extern int zero_count = 0;

extern int brk = FALSE;							// Set TRUE when the syntax goes wrong.
extern int brk2 = FALSE;
extern int valid = TRUE;						// Syntax if found wrong, only then invalid.

extern size_t TABLES_JSON_DEFAULT = 48;
extern size_t EXPANSION_SIZE = 22;










/* Implementation of DB operations. */

extern void clearEntity(char *str);
extern int checkDbExistence(int msg);
extern int checkTableExistence(int msg);
extern void tableStructure();
extern void allDatabases();
extern void allTables();
extern void checkDataType();
extern void makeTable();










#endif
