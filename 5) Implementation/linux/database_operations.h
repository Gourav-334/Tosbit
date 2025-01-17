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

#include "utility_box.h"










/* Major buffer string & other variables. */

extern FILE *fptr, *fptr2;
extern FILE *cache;

extern char command[COMMAND_MAX_LENGTH];
extern char database[DATABASE_MAX_LENGTH];
extern char table[TABLE_MAX_LENGTH];
extern char directory[DIRECTORY_MAX_LENGTH];
extern char buffer[BUFFER_MAX_LENGTH];
extern char dataType[DATA_TYPE_MAX_LENGTH];
extern char attribute[ATTRIBUTE_MAX_LENGTH];

extern char flusher;

extern int state;							// Main automaton
extern int state2;							// Table attribute automaton
extern int zero_count;

extern int brk;								// Set TRUE when the syntax goes wrong.
extern int brk2;
extern int valid;							// Syntax if found wrong, only then invalid.
extern int TABLES_JSON_DEFAULT;
extern int EXPANSION_SIZE;










/* Implementation of DB operations. */

extern void clearEntity(char *str);
extern int checkDbExistence(int msg);
extern int checkTableExistence(int msg);
extern void tableStructure();
extern void allDatabases();
extern void allTables();
extern void checkDataType();
extern void makeTable();
extern void makeDb();
extern void deleteTable();
extern void deleteDb();
extern void clearTable();
extern void clearDb();
extern void pushRow();










#endif
