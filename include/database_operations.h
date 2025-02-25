#ifndef DATABASE_OPERATIONS_H
	#define DATABASE_OPERATIONS_H

#define TRUE 1
#define FALSE 0





#define COMMAND_MAX_LENGTH 512
#define DATABASE_MAX_LENGTH 33
#define TABLE_MAX_LENGTH 33
#define DIRECTORY_MAX_LENGTH 257
#define BUFFER_MAX_LENGTH 257

#define DATA_TYPE_MAX_LENGTH 7
#define ATTRIBUTE_MAX_LENGTH 33
#define KEY_MAX_LENGTH 8
#define VALUE_MAX_LENGTH 33
#define PATH_MAX_LENGTH 257

#define INT_TO_ASCII_LIMIT 8





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility_box.h"
#include "transition_tool.h"
#include "queue.h"










/* Major buffer string & other variables. */

extern FILE *fptr, *fptr2;		// MAKE IT LOCAL!
extern FILE *cache;				// MAKE IT LOCAL!

extern char command[COMMAND_MAX_LENGTH];
extern char database[DATABASE_MAX_LENGTH];
extern char table[TABLE_MAX_LENGTH];
extern char directory[DIRECTORY_MAX_LENGTH];	// MAKE IT LOCAL!
extern char buffer[BUFFER_MAX_LENGTH];
extern char buffer2[BUFFER_MAX_LENGTH];
extern char dataType[DATA_TYPE_MAX_LENGTH];
extern char attribute[ATTRIBUTE_MAX_LENGTH];
extern char key[KEY_MAX_LENGTH];
extern char value[VALUE_MAX_LENGTH];
extern char pureValue[VALUE_MAX_LENGTH];
extern char ascii[INT_TO_ASCII_LIMIT];

extern int state;							// Main automaton
extern int state2;							// Used for "table attribute" & "data types"
extern int zero_count;

extern int brk;								// Set TRUE when the syntax goes wrong.
extern int brk2;
extern int valid;							// Syntax if found wrong, only then invalid.










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
extern void deleteTable(int msg);
extern void deleteDb(int msg);
extern void clearTable();
extern void clearDb();
extern int checkUnique(char value[], int currArg, int totalArg);
extern int typeParser();
extern void pushRow();
extern void selectionParser();
extern void conditionParser();
extern void allRows();










#endif
