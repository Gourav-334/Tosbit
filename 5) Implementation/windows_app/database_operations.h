#ifndef DATABASE_OPERATIONS_H
	#define DATABASE_OPERATIONS_H

#define COMMAND_MAX_LENGTH 257
#define DATABASE_MAX_LENGTH 17
#define TABLE_MAX_LENGTH 33
#define DIRECTORY_MAX_LENGTH 129
#define BUFFER_MAX_LENGTH 133





#include <stdio.h>
#include "console_colour.h"










/* Major buffer string & other variables. */

FILE *fptr;

char command[COMMAND_MAX_LENGTH];
char database[DATABASE_MAX_LENGTH];
char table[TABLE_MAX_LENGTH];
char directory[DIRECTORY_MAX_LENGTH];
char buffer[BUFFER_MAX_LENGTH];





/* Implementation of DB operations. */

void colouredMessage(char *colour, char *str);
void clearEntity(char *str);

void checkDbExistence();
void checkTableExistence();
void tableStructure();
void allDatabases();
void allTables();










#endif