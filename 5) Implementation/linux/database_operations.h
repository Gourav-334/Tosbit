#ifndef DATABASE_OPERATIONS_H
	#define DATABASE_OPERATIONS_H

#define COMMAND_MAX_LENGTH 257
#define DATABASE_MAX_LENGTH 17
#define TABLE_MAX_LENGTH 17
#define DIRECTORY_MAX_LENGTH 129
#define BUFFER_MAX_LENGTH 257

#define DATA_TYPE_MAX_LENGTH 7
#define ATTRIBUTE_MAX_LENGTH 17





#include <stdio.h>
#include <stdlib.h>
#include <string.h>










/* Major buffer string & other variables. */

FILE *fptr;

char command[COMMAND_MAX_LENGTH];
char database[DATABASE_MAX_LENGTH];
char table[TABLE_MAX_LENGTH];
char directory[DIRECTORY_MAX_LENGTH];
char buffer[BUFFER_MAX_LENGTH];
char dataType[DATA_TYPE_MAX_LENGTH];
char attribute[ATTRIBUTE_MAX_LENGTH];

char flusher;

int state = 0;							// Main automaton
int state2 = 0;							// Table attribute automaton
int zero_count = 0;

int brk = FALSE;						// Set TRUE when the syntax goes wrong.
int brk2 = FALSE;
int valid = TRUE;						// Syntax if found wrong, only then invalid.

size_t TABLES_JSON_DEFAULT = 48;
size_t EXPANSION_SIZE = 22;










/* Implementation of DB operations. */

void clearEntity(char *str);
int checkDbExistence(int msg);
int checkTableExistence(int msg);
void tableStructure();
void allDatabases();
void allTables();
void checkDataType();
void makeTable();










#endif
