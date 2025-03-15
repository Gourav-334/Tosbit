/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef DATABASE_OPERATIONS_H
	#define DATABASE_OPERATIONS_H


#define TRUE 	1 		// Macro to imitate boolean TRUE behaviour.
#define FALSE 	0		// Macro to imitate boolean FALSE behaviour.

#define COMMAND_MAX_LENGTH 		512			// Max size a command can be of.
#define DATABASE_MAX_LENGTH 	33			// Max size a database name can be of.
#define TABLE_MAX_LENGTH 		33			// Max size a table name can be of.
#define DIRECTORY_MAX_LENGTH 	257			// Max size a directory path can be of.
#define BUFFER_MAX_LENGTH 		257			// Max size a buffer can be of.
#define FEEDBACK_BUFFER_SIZE 	512			// Max size the feedback buffer can be of.
#define DATA_TYPE_MAX_LENGTH 	7			// Max size a data type name can be of.
#define ATTRIBUTE_MAX_LENGTH 	33			// Max size an attribute name can be of.
#define KEY_MAX_LENGTH 			8			// Max size a key type can be of.
#define VALUE_MAX_LENGTH 		33			// Max size an attribute value can be of.
#define INT_TO_ASCII_LIMIT 		8			// Max size an ASCII buffer can be of.





#include <stdio.h>			// Standard input/output header.
#include <stdlib.h>			// Standard library functions header.
#include <string.h>			// String utility header.


#include "utility_box.h"			// Custom utility header.
#include "transition_tool.h"		// DFA state transition management header.
#include "queue.h"					// Queue data structure utility header.










/* Major buffer string & other variables. */

extern FILE *fptr, *fptr2;		// File pointers used in file operations.
extern FILE *cache;				// File pointer used specifically for cache files.
extern char *feedback;			// The final string printed after full execution of command.


extern char command 		[COMMAND_MAX_LENGTH];		// Command input by user.
extern char database 		[DATABASE_MAX_LENGTH];		// Stores name of the database.
extern char table 			[TABLE_MAX_LENGTH];			// Stores name of the table.
extern char directory 		[DIRECTORY_MAX_LENGTH];		// Continuously formatted directory path.
extern char buffer 			[BUFFER_MAX_LENGTH];		// Intermediate buffer for many operations.
extern char buffer2 		[BUFFER_MAX_LENGTH];		// Another buffer for some cases.
extern char dataType 		[DATA_TYPE_MAX_LENGTH];		// Stores data type of an attribute at times.
extern char attribute 		[ATTRIBUTE_MAX_LENGTH];		// Stores attribute name at times.
extern char key 			[KEY_MAX_LENGTH];			// Stores key type at times.
extern char value 			[VALUE_MAX_LENGTH];			// Stores attribute value at times.
extern char pureValue 		[VALUE_MAX_LENGTH];			// Stores formatted attribute value at times.
extern char ascii 			[INT_TO_ASCII_LIMIT];		// Intermediate buffer for 'integer to ASCII'.
extern char feedbackBuffer 	[FEEDBACK_BUFFER_SIZE];		// Intermediate buffer to store feedback info.


extern int 		state;					// Main automaton
extern int 		state2;					// Used for "table attribute" & "data types"
extern int 		breaker;				// Set TRUE when syntax goes wrong in main DFA..
extern int 		breaker2;				// Set TRUE when syntax goes wrong in secondary DFA.
extern int 		valid;					// Syntax if found wrong, only then invalid.
extern int 		serverMode;				// Tells if database is currently connected to server.
extern size_t 	feedbackSize;			// Tracks size for the 'feedback' string.










/* Implementation of DB operations. */

extern void extendFeedback(char message[]);		// Stores all bytes in final feedback.
extern void clearEntity(char *str);				// This function clears a string, identified through entered value of string.
extern int 	checkDbExistence(int msg);			// Checks if the user requested database exists or not.
extern int 	checkTableExistence(int msg);		// Checks if a user requested table exists or not.
extern void tableStructure();					// Shows structure of the requested table (console design comes before fetching).
extern void allDatabases();						// Shows all the available databases.
extern void allTables();						// Shows all available tables in the online database.
extern void checkDataType();					// This funstion checks if a invalid data type was passed.
extern void makeTable();						// Creates a table & configures many files.
extern void makeDb();							// Make a database on user's request.
extern void deleteTable(int msg);				// Deleting a table.
extern void deleteDb(int msg);					// Deleting a database.
extern void clearTable();						// Clears any requested table (clears of all data it holds).
extern void clearDb();							// Clear all the tables present in a database.
extern int 	checkUnique(						// Checking if unique value exists or not. (UNTESTED ON UNIQUE KEYS).
	char value[], int currArg, int totalArg
);
extern int 	typeParser();						// Data type parsing & validating automaton.
extern void pushRow();							// Pushing row into a table.
extern void selectionParser();					// Parses the selection arguments & provides feedback on its integrity.
extern void allRows();							// Parser to check integrity of conditional syntax (after WHERE).
extern void updateParser();						// Update parser parses & validates the first buffer in UPDATE command.
extern void updateAll(							// Updating all rows for a given value for each.
	struct Queue *argumentQueue,
	struct Queue *valueQueue
);










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */