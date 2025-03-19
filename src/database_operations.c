/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/database_operations.h"




















/* Global initializations */

FILE *fptr 		= NULL;
FILE *fptr2 	= NULL;
FILE *cache 	= NULL;
char *feedback 	= NULL;


char command 		[COMMAND_MAX_LENGTH] 	= {0};
char database 		[DATABASE_MAX_LENGTH] 	= {0};
char table 			[TABLE_MAX_LENGTH] 		= {0};
char directory 		[DIRECTORY_MAX_LENGTH] 	= {0};
char buffer 		[BUFFER_MAX_LENGTH] 	= {0};
char buffer2 		[BUFFER_MAX_LENGTH] 	= {0};
char dataType 		[DATA_TYPE_MAX_LENGTH] 	= {0};
char attribute 		[ATTRIBUTE_MAX_LENGTH] 	= {0};
char key 			[KEY_MAX_LENGTH] 		= {0};
char value 			[VALUE_MAX_LENGTH] 		= {0};
char pureValue		[VALUE_MAX_LENGTH] 		= {0};
char ascii 			[INT_TO_ASCII_LIMIT] 	= {0};
char feedbackBuffer [FEEDBACK_BUFFER_SIZE] 	= {0};


int state 			= 0;
int state2 			= 0;
int breaker 		= FALSE;
int breaker2 		= FALSE;
int valid 			= TRUE;
int serverMode 		= FALSE;
size_t feedbackSize = 0;




















/* Stores all bytes in final feedback. */

void extendFeedback(char message[])
{
	/* Declarations */

	char *ptr = NULL;


	/* Extending size of 'feedback' by 'message' string length with NULL safety. */

	if (feedback==NULL)
	{
		feedback = (char*)malloc(1*sizeof(char)); feedback[0] = '\0';
		if (feedback==NULL) {printf("ERROR: Can't allocate first byte!"); return;}
		else {feedbackSize++;}
	}

	ptr = (char*)realloc(feedback, (size_t)(feedbackSize + strlen(message) + 1)*sizeof(char));

	if (ptr==NULL) {printf("ERROR: Can't reallocate feedback!"); return;}
	feedback = ptr;



	/* Appending 'message' at the end of 'feedback'. */

	strcat(feedback, message);
	feedbackSize += (size_t)strlen(message);
}










/* This function clears a string, identified through entered value of string. */

void clearEntity(char *str)
{
	if (!strcmp(str,"command")) 			{memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"database")) 		{memset(database, 0, DATABASE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"table")) 			{memset(table, 0, TABLE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"directory")) 		{memset(directory, 0, DIRECTORY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"buffer")) 		{memset(buffer, 0, BUFFER_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"buffer2")) 		{memset(buffer2, 0, BUFFER_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"dataType")) 		{memset(dataType, 0, DATA_TYPE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"attribute")) 		{memset(attribute, 0, ATTRIBUTE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"key")) 			{memset(key, 0, KEY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"value")) 			{memset(value, 0, VALUE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"pureValue")) 		{memset(pureValue, 0, VALUE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"feedback")) 		{memset(feedback, 0, (size_t)feedbackSize);}
	else if (!strcmp(str,"feedbackBuffer")) {memset(feedbackBuffer, 0, FEEDBACK_BUFFER_SIZE*sizeof(char));}

	else {extendFeedback("ERROR: clearEntity() used for unknown string!\n");}
}










/* Checks if the user requested database exists or not. */

int checkDbExistence(int msg)
{
	/* Initializations */

	int existence;


	/* Formatting 'directory' to path for tables.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/tables.tosbit", database);
	fptr = fopen(directory, "r");


	/* Checking existence of database through existence of tables.tosbit */

	if (fptr==NULL && msg==TRUE)
	{
		existence = FALSE;

		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No database named \"%s\" exists!", database);
		extendFeedback(feedbackBuffer);
		
		clearEntity("database");
	}
	else if (fptr==NULL && msg==FALSE) {existence = FALSE;}
	else if (fptr!=NULL && msg==TRUE)
	{
		existence = TRUE;

		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: Database %s online!", database);
		extendFeedback(feedbackBuffer);

		fclose(fptr);
	}
	else if (fptr!=NULL && msg==FALSE) {existence = TRUE; fclose(fptr);}


	/* Returning 'true' if database exists, else 'false'. */

	return existence;
}










/* Checks if a user requested table exists or not. */

int checkTableExistence(int msg)
{
	/* Initializations */

	int existence;


	/* Formatting 'directory' to path for details.tosbit */

	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);
	fptr = fopen(directory, "r");


	/* Checking if a database is opened or not & existence of details.tosbit */

	if (strlen(database)==0 && msg==TRUE) {extendFeedback("ERROR: No database opened yet!");}
	else if (fptr==NULL && msg==FALSE) {existence = FALSE;}
	else if (fptr==NULL && msg==TRUE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		clearEntity("table");

		existence = FALSE;
	}
	else if (fptr!=NULL && msg==FALSE) {existence = TRUE; fclose(fptr);}
	else if (fptr!=NULL && msg==TRUE) {tableStructure(); existence = TRUE;}


	/* Returning 'true' if table exists, else 'false'. */

	return existence;
}










/* Shows structure of the requested table (console design comes before fetching). */

void tableStructure()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int largestAttribute, largestDataType, largestKey;
	int largestAttributeN = strlen("Attributes"), largestDataTypeN = strlen("Data Types"), largestKeyN = strlen("Key");
	int charsPrinted = 0, totalAttributes = 0;


	/* Opening metadata.tosbit & giving safety against NULL file descriptor. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/metadata.tosbit", database, table);
	fptr = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Metadata for table \"%s\" not found!", table);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* Reading & storing maximum attribute name, data type name or key name length. */

	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestAttribute = atoi(metaBuff);
	fseek(fptr, 1, SEEK_CUR);

	memset(metaBuff, 0, sizeof(metaBuff));
	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestDataType = atoi(metaBuff);
	fseek(fptr, 1, SEEK_CUR);

	memset(metaBuff, 0, sizeof(metaBuff));
	for (int i=0; i<2; i++)
	{
		c = fgetc(fptr);
		if (c==' ') {break;}

		metaBuff[i] = c;
	}
	largestKey = atoi(metaBuff);


	/* Opening details.json & giving safety against NULL file descriptor. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);
	fptr2 = fopen(directory, "r");

	if (fptr2==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Details for \"%s\" not found!", table);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* Printing upper part of the console-table (the header of the table). */

	extendFeedback("+"); for (int i=0; i<largestAttribute; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestDataType; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestKey; i++) {extendFeedback("-");} extendFeedback("+\n");

	extendFeedback("|Attributes"); for (int i=0; i<largestAttribute-strlen("Attributes"); i++) {extendFeedback(" ");}
	extendFeedback("|Data Types"); for (int i=0; i<largestDataType-strlen("Data Types"); i++) {extendFeedback(" ");}
	extendFeedback("|Keys"); for (int i=0; i<largestKey-strlen("Keys"); i++) {extendFeedback(" ");} extendFeedback("|\n");

	extendFeedback("+"); for (int i=0; i<largestAttribute; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestDataType; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestKey; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Printing Lower part of console-table (about all attributes & their properties). */

	while (!reachedEOF(fptr2))
	{
		/* Attributes */

		charsPrinted = 0; extendFeedback("|"); c = fgetc(fptr2);

		do {
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++; c = fgetc(fptr2);
		}
		while (c!=' ' && c!=',');

		for (int i=0; i<largestAttribute-charsPrinted; i++) {extendFeedback(" ");}
		if (c==' ') {fseek(fptr2, (ATTRIBUTE_MAX_LENGTH-1)-charsPrinted, SEEK_CUR);}

		if (charsPrinted > largestAttributeN) {largestAttributeN = charsPrinted;}
		

		/* Data Type */

		charsPrinted = 0; extendFeedback("|"); c = fgetc(fptr2);

		do {
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++; c = fgetc(fptr2);
		}
		while (c!=' ' && c!=',');

		for (int i=0; i<largestDataType-charsPrinted; i++) {extendFeedback(" ");}
		if (c==' ') {fseek(fptr2, (DATA_TYPE_MAX_LENGTH-1)-charsPrinted, SEEK_CUR);}

		if (charsPrinted > largestDataTypeN) {largestDataTypeN = charsPrinted;}


		/* Key Type */

		charsPrinted = 0; extendFeedback("|"); c = fgetc(fptr2);

		do {
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++; c = fgetc(fptr2);
		}
		while (c!=' ' && c!=',');

		for (int i=0; i<largestKey-charsPrinted; i++) {extendFeedback(" ");}
		if (c==' ') {fseek(fptr2, ((KEY_MAX_LENGTH-1)-charsPrinted)+2, SEEK_CUR);}
		else if (c==',') {fseek(fptr2, 2, SEEK_CUR);} extendFeedback("|\n");

		if (charsPrinted > largestKeyN) {largestKeyN = charsPrinted;}


		/* Counting each encountered attribute for stats. */

		totalAttributes++;


		/* Safety mechanism to avoid reading garbage after EOF & then running in infinite loop. */

		c = fgetc(fptr2);
		if (c!='\n') {break;}
		else if (c=='\n') {continue;}
	}

	extendFeedback("+"); for (int i=0; i<largestAttribute; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestDataType; i++) {extendFeedback("-");}
	extendFeedback("+"); for (int i=0; i<largestKey; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Safely closing file descriptor. */

	fclose(fptr2);


	/* Writing newer largest attributes, data types & keys (if any). */

	if (largestAttributeN<largestAttribute)
	{
		fseek(fptr, 0, SEEK_SET); fputs(itoa(largestAttributeN, ascii), fptr);
		if (largestAttributeN<10) {fputc(' ', fptr);}
	}

	if (largestDataTypeN<largestDataType)
	{
		fseek(fptr, 3, SEEK_SET); fputs(itoa(largestDataTypeN, ascii), fptr);
		if (largestDataTypeN<10) {fputc(' ', fptr);}
	}

	if (largestKeyN<largestKey)
	{
		fseek(fptr, 6, SEEK_SET); fputs(itoa(largestKeyN, ascii), fptr);
	}


	/* Safely closing file descriptor. */

	fclose(fptr);


	/* Showing total attributes encountered so far. */

	clearEntity("feedbackBuffer");
	snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: Table contains %d attributes.", totalAttributes);
	extendFeedback(feedbackBuffer);
}










/* Shows all the available databases. */

void allDatabases()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int largestDb, largestDbN = strlen("Databases");;
	int charsPrinted = 0, totalDb = 0;


	/* Opening metadata.tosbit with safety for NULL file descriptor. */

	fptr = fopen("data/metadata.tosbit", "r+");
	if (fptr==NULL) {extendFeedback("ERROR: Data metadata not found!"); return;}


	/* Reading length of largest database name. */

	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestDb = atoi(metaBuff);
	

	/* Opening databases.tosbit with safety for NULL file descriptor. */

	fptr2 = fopen("data/databases.tosbit", "r");
	if (fptr2==NULL) {extendFeedback("ERROR: Information for databases not found!"); return;}


	/* Printing header of the console-table (header of table). */

	extendFeedback("+"); for (int i=0; i<largestDb; i++) {extendFeedback("-");} extendFeedback("+\n");
	extendFeedback("|Databases"); for (int i=0; i<largestDb-strlen("Databases"); i++) {extendFeedback(" ");} extendFeedback("|\n");
	extendFeedback("+"); for (int i=0; i<largestDb; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Printing the lower part of the console-table (names of all databases). */

	while (!reachedEOF(fptr2))
	{
		/* Printing a row on console for a database. */

		charsPrinted = 0;

		extendFeedback("|"); c = fgetc(fptr2);
		if (c=='\t') {extendFeedback("\b"); fseek(fptr2, DATABASE_MAX_LENGTH-1, SEEK_CUR); continue;}

		do {
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++; c = fgetc(fptr2);
		}
		while (c!=' ' && c!=',');

		for (int i=0; i<largestDb-charsPrinted; i++) {extendFeedback(" ");} extendFeedback("|\n");

		if (charsPrinted > largestDbN) {largestDbN = charsPrinted;}


		/* Counting each encountered database for stats. */

		totalDb++;


		/* Taking action depending on the position of FD cursor (space, \n or EOF). */

		if (c==' ')
		{
			fseek(fptr2, ((DATABASE_MAX_LENGTH-1)-charsPrinted)-1, SEEK_CUR);


			/* Checking next byte & chossing action accordingly. */

			c = fgetc(fptr2);
			if (c=='\n') {continue;}
			else if (reachedEOF(fptr2)) {break;}
		}
		else if (c=='\n') {continue;}
		else if (reachedEOF(fptr2)) {break;}
	}


	/* Printing tail of the console-table (the last line). */

	extendFeedback("+"); for (int i=0; i<largestDb; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Writing new largest database name length (if any). */

	if (largestDbN < largestDb)
	{
		fseek(fptr, 0, SEEK_SET); fputs(itoa(largestDbN, ascii), fptr);
		if (largestDbN<10) {fputc(' ', fptr);}
	}


	/* Safely closing the file descriptor. */

	fclose(fptr); fclose(fptr2);


	/* Printing total number of databases as stats. */

	clearEntity("feedbackBuffer");
	snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: %d databases found.", totalDb);
	extendFeedback(feedbackBuffer);
}










/* Shows all available tables in the online database. */

void allTables()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int largestTable, largestTableN = strlen("Tables");
	int charsPrinted = 0, totalTable = 0;


	/* Formatting 'directory' to open db_name/metadata.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/metadata.tosbit", database);


	/* Opening metadata.tosbit with safety for NULL file descriptor. */

	fptr = fopen(directory, "r+");
	if (fptr==NULL) {extendFeedback("ERROR: Data metadata not found!"); return;}


	/* Reading length of largest table name. */

	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestTable = atoi(metaBuff);
	

	/* Opening tables.tosbit with safety for NULL file descriptor. */
	
	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/tables.tosbit", database);

	fptr2 = fopen(directory, "r");
	if (fptr2==NULL) {extendFeedback("ERROR: No database opened yet!"); return;}


	/* Printing header of the console-table (header of table). */

	extendFeedback("+"); for (int i=0; i<largestTable; i++) {extendFeedback("-");} extendFeedback("+\n");
	extendFeedback("|Tables"); for (int i=0; i<largestTable-strlen("Tables"); i++) {extendFeedback(" ");} extendFeedback("|\n");
	extendFeedback("+"); for (int i=0; i<largestTable; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Printing the lower part of the console-table (names of all tables). */

	while (!reachedEOF(fptr2))
	{
		/* Printing a row on console for a table & skipping '\t' rows. */

		charsPrinted = 0;

		extendFeedback("|"); c = fgetc(fptr2);
		if (c=='\t') {extendFeedback("\b"); fseek(fptr2, TABLE_MAX_LENGTH-1, SEEK_CUR); continue;}

		do {
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++; c = fgetc(fptr2);
		}
		while (c!=' ' && c!=',');

		for (int i=0; i<largestTable-charsPrinted; i++) {extendFeedback(" ");} extendFeedback("|\n");
		if (charsPrinted > largestTableN) {largestTableN = charsPrinted;}


		/* Counting each encountered table for stats. */

		totalTable++;


		/* Taking action depending on the position of FD cursor (space, \n or EOF). */

		if (c==' ')
		{
			fseek(fptr2, ((TABLE_MAX_LENGTH-1)-charsPrinted)-1, SEEK_CUR);


			/* Checking next byte & chossing action accordingly. */

			c = fgetc(fptr2);
			if (c=='\n') {continue;}
			else if (reachedEOF(fptr2)) {break;}
		}
		else if (c=='\n') {continue;}
		else if (reachedEOF(fptr2)) {break;}
	}


	/* Printing tail of the console-table (the last line). */

	extendFeedback("+"); for (int i=0; i<largestTable; i++) {extendFeedback("-");} extendFeedback("+\n");


	/* Writing new largest table name length (if any). */

	if (largestTableN < largestTable)
	{
		fseek(fptr, 0, SEEK_SET); fputs(itoa(largestTableN, ascii), fptr);
		if (largestTableN<10) {fputc(' ', fptr);}
	}


	/* Safely closing the file descriptor. */

	fclose(fptr); fclose(fptr2);


	/* Printing total number of databases as stats. */

	clearEntity("feedbackBuffer");
	snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: %d tables found.", totalTable);
	extendFeedback(feedbackBuffer);
}










/* This funstion checks if a invalid data type was passed. */

void checkDataType()
{
	/* Initializations */

	int state3 = 0, breaker3 = 0, error = FALSE;



	/* Parsing data type syntax with Deterministic Finite Automata (DFA). */

	for (int i=0; i<strlen(dataType); i++)
	{
		switch (state3)
		{
			case 0: changeState(dataType[i], "iIsSfFbBmM", "1,1,4,4,10,10,16,16,20,20", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 1: changeState(dataType[i], "nN", "2,2", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 2: changeState(dataType[i], "tT", "3,3", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 3: changeState(dataType[i], " ", "3", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 4: changeState(dataType[i], "tT", "5,5", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 5: changeState(dataType[i], "rR", "6,6", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 6: changeState(dataType[i], "iI", "7,7", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 7: changeState(dataType[i], "nN", "8,8", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 8: changeState(dataType[i], "gG", "9,9", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 9: changeState(dataType[i], " ", "9", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 10: changeState(dataType[i], "lL", "11,11", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 11: changeState(dataType[i], "oO", "12,12", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 12: changeState(dataType[i], "aA", "13,13", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 13: changeState(dataType[i], "tT", "14,14", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 14: changeState(dataType[i], " ", "14", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 16: changeState(dataType[i], "oO", "17,17", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 17: changeState(dataType[i], "oO", "18,18", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 18: changeState(dataType[i], "lL", "19,19", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 19: changeState(dataType[i], " ", "19", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 20: changeState(dataType[i], "eE", "21,21", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 21: changeState(dataType[i], "dD", "22,22", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 22: changeState(dataType[i], "iI", "23,23", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 23: changeState(dataType[i], "aA", "24,24", &state3, 25); breakValue(&state3, 25, &breaker3); break;
			case 24: changeState(dataType[i], " ", "24", &state3, 25); breakValue(&state3, 25, &breaker3); break;
		}


		/* Breaking from loop early if DFA reaches dump state (error). */

		if (breaker3==TRUE) {breaker3 = FALSE; break;}
	}





	/* Taking decision or giving feedback as per DFA's stop state. */

	switch (state3)
	{
		case 0: clearEntity("feedbackBuffer");
				snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Invalid data type passed!", dataType);
				extendFeedback(feedbackBuffer);
				break;

		case 1: extendFeedback("ERROR: Did you meant INT?"); break;
		case 2: extendFeedback("ERROR: Did you meant INT?"); break;
		case 4: extendFeedback("ERROR: Did you meant STRING?"); break;
		case 5: extendFeedback("ERROR: Did you meant STRING?"); break;
		case 6: extendFeedback("ERROR: Did you meant STRING?"); break;
		case 7: extendFeedback("ERROR: Did you meant STRING?"); break;
		case 8: extendFeedback("ERROR: Did you meant STRING?"); break;
		case 10: extendFeedback("ERROR: Did you meant FLOAT?"); break;
		case 11: extendFeedback("ERROR: Did you meant FLOAT?"); break;
		case 12: extendFeedback("ERROR: Did you meant FLOAT?"); break;
		case 13: extendFeedback("ERROR: Did you meant FLOAT?"); break;
		case 16: extendFeedback("ERROR: Did you meant BOOL?"); break;
		case 17: extendFeedback("ERROR: Did you meant BOOL?"); break;
		case 18: extendFeedback("ERROR: Did you meant BOOL?"); break;
		case 20: extendFeedback("ERROR: Did you meant MEDIA?"); break;
		case 21: extendFeedback("ERROR: Did you meant MEDIA?"); break;
		case 22: extendFeedback("ERROR: Did you meant MEDIA?"); break;
		case 23: extendFeedback("ERROR: Did you meant MEDIA?"); break;
		case 25: state2 = 8; error = TRUE; break;
	}
}










/* Creates a table & configures many files. */

void makeTable()
{
	/* Initialization */

	char decision, c;
	char metaBuff[2] = {0};
	int write = TRUE, uniqueKey = FALSE;
	int largestAttribute = 10, largestDataType = 10, largestKey = 6;


	/* Queue structure to handle attributes. */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll
	};



	/* Checking if database & table exists or not. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); write = FALSE; return;}
	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==TRUE))
	{
		extendFeedback("STAT: Table already exists!");
		write = FALSE;
	}
	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==FALSE))
	{
		/* Checking table's name for safety. */

		if (illegalChars(table, "+-*/%!=&|")==TRUE)
		{
			extendFeedback(
				"ERROR: Please don't use operators (+, -, *, /, %%, !, =, &, |) in name of table."
			);

			return;
		}


		/* Checking if table's name if larger than existing tables/header. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/metadata.tosbit", database);


		/* Opening metadata.tosbit with safety for NULL file descriptor. */

		fptr = fopen(directory, "r+");
		if (fptr==NULL) {extendFeedback("ERROR: Database metadata not found!"); return;}


		/* The check & action as per that. */

		for (int i=0; i<2; i++) {c = fgetc(fptr); if (c!=' ') {metaBuff[i] = c;}}

		if ((int)strlen(table)>atoi(metaBuff))
			{fseek(fptr, 0, SEEK_SET); fputs(itoa((int)strlen(table), ascii), fptr);}


		/* Safely closing the file descriptor. */

		fclose(fptr);


		/* Formatting 'directory' to open tables.tosbit. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.tosbit", database);


		/* Opening table.tosbit with safety for NULL file descriptor. */

		fptr = fopen(directory, "r+");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Table information for \"%s\" not found!", database);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Writing name of table in tables.tosbit, if a new table is made (no overwriting). */

		fseek(fptr, 0, SEEK_END);
		if (!newFile(fptr)) {fputc('\n', fptr);}
		fputs(table, fptr);
		for (int i=0; i<(TABLE_MAX_LENGTH-1)-strlen(table); i++) {fputc(' ', fptr);}


		/* Safely closing the file descriptor. */

		fclose(fptr);
	}



	/* If new table is made, or if an exisiting table is overwritten. */

	if (write==TRUE)
	{
		/* Making table's folder directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "mkdir data/%s/%s", database, table);
		system(directory);


		/* Creating rows.tosbit */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "touch data/%s/%s/rows.tosbit", database, table);
		system(directory);


		/* Opening tbl_name/metadata.tosbit in write mode (creating it). */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/metadata.tosbit", database, table);


		/* Having safety for NULL file descriptor. */

		fptr = fopen(directory, "w+");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through data/%s/%s!", database, table);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Writing default configurations to metadata.tosbit (required further too) */

		fputs("10,10,6 ", fptr);



		/* Creating rows.tosbit */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.tosbit", database, table);


		/* Checking file descriptor with NULL safety. */

		fptr2 = fopen(directory, "w");

		if (fptr2==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through data/%s/%s!", database, table);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Creating details.tosbit */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);


		/* Checking file descriptor with NULL safety. */

		fptr2 = fopen(directory, "w+");

		if (fptr2==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through data/%s/%s!", database, table);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* 'buffer' contains everything within () that user passed with MAKE TABLE command. */

		for (int i=0; i<strlen(buffer); i++)
		{
			/* Fetching data type by user in series. */

			while (buffer[i]==' ') {i++;} clearEntity("dataType");
			while (buffer[i]!=' ') {dataType[strlen(dataType)] = buffer[i]; i++;}


			/* Knowing the data type by its initials (already verified by DFA). */

			if (dataType[0]=='i' || dataType[0]=='I') 		{clearEntity("dataType"); strcpy(dataType,"int");}
			else if (dataType[0]=='s' || dataType[0]=='S') 	{clearEntity("dataType"); strcpy(dataType,"string");}
			else if (dataType[0]=='f' || dataType[0]=='F') 	{clearEntity("dataType"); strcpy(dataType,"float");}
			else if (dataType[0]=='b' || dataType[0]=='B') 	{clearEntity("dataType"); strcpy(dataType,"bool");}
			else if (dataType[0]=='m' || dataType[0]=='M') 	{clearEntity("dataType"); strcpy(dataType,"media");}
			
			newline_remover(dataType);


			/* Fetching attribute's name by user in series. */

			while (buffer[i]==' ') {i++;} clearEntity("attribute");
			while (buffer[i]!=',' && i!=strlen(buffer)) {attribute[strlen(attribute)] = buffer[i]; i++;}


			/* Incase attributes with same name are encountered. */

			if ((attributeQueue.getIndex(&attributeQueue, attribute)>=0) && (attributeQueue.n>0))
				{extendFeedback("ERROR: Each attribute must have a unique name!"); deleteTable(FALSE); return;}


			/* Enqueueing attribute to the end of attributeQueue. */

			attributeQueue.queue(&attributeQueue, attribute);



			/* Writing metadata to details.json with key constraints. */

			clearEntity("key");


			/* Assigning keys, avoiding multiple unique keys & hardwiring file keys to media types. */

			if ((dataType[0]=='m' || dataType[0]=='M') && !(attribute[0]=='$')) {strcpy(key,"file");}
			else if ((dataType[0]=='m' || dataType[0]=='M') && (attribute[0]=='$'))
			{
				clearEntity("directory");
				snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);
				system(directory);
				extendFeedback("ERROR: Media attributes are hardwired to file keys!");

				return;
			}
			else if (attribute[0]=='$' && uniqueKey==FALSE) {strcpy(key,"unique"); uniqueKey = TRUE;}
			else if (attribute[0]=='$' && uniqueKey==TRUE)
			{
				clearEntity("directory");
				snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);
				system(directory);
				extendFeedback("ERROR: A table can't have multiple unique keys!");

				return;
			}
			else {strcpy(key,"regular");}
			newline_remover(key);



			/* Writing default configurations to details.tosbit */

			fputs(attribute, fptr2);
			for (int i=0; i<(ATTRIBUTE_MAX_LENGTH-1)-strlen(attribute); i++) {fputc(' ', fptr2);}
			fputc(',', fptr2);

			fputs(dataType, fptr2);
			for (int i=0; i<(DATA_TYPE_MAX_LENGTH-1)-strlen(dataType); i++) {fputc(' ', fptr2);}
			fputc(',', fptr2);

			fputs(key, fptr2);
			for (int i=0; i<(KEY_MAX_LENGTH-1)-strlen(key); i++) {fputc(' ', fptr2);}
			fputc(',', fptr2);


			/* Writing the largest value for each attribute (attribute name length by default). */

			fputs(itoa((int)strlen(attribute),ascii), fptr2);
			if (strlen(attribute)<10) {fputc(' ', fptr2);}



			/* Modifying tbl_name/metadata.tosbit as per recent fetches. */

			if ((int)strlen(attribute)>largestAttribute)
				{fseek(fptr, 0, SEEK_SET); fputs(itoa((int)strlen(attribute), ascii), fptr);}

			if ((int)strlen(dataType)>largestDataType)
				{fseek(fptr, 3, SEEK_SET); fputs(itoa((int)strlen(dataType), ascii), fptr);}

			if ((int)strlen(key)>largestKey)
				{fseek(fptr, 6, SEEK_SET); fputs(itoa((int)strlen(key), ascii), fptr);}



			/* Putting an '\n' if there are are attributes further. */

			if (buffer[i]==',') {fputc('\n', fptr2);}
		}



		/* Safely closing both the file descriptors. */

		fclose(fptr); fclose(fptr2);


		/* Clearing the attribute queue. */

		attributeQueue.clear(&attributeQueue);


		/* Displaying message for successful table creation. */

		extendFeedback("OK: Table created successfully!");
	}
}










/* Make a database on user's request. */

void makeDb()
{
	/* Initialization */

	char decision, c;
	char metaBuff[2] = {0};
	int write = TRUE, uniqueKey = FALSE;



	/* Checking if database & database exists or not. */

	if (checkDbExistence(FALSE)==TRUE)
	{
		extendFeedback("STAT: Database already exists!");
		write = FALSE;
	}
	else if (checkDbExistence(FALSE)==FALSE)
	{
		/* Checking database's name for safety. */

		if (illegalChars(database, "+-*/%!=&|")==TRUE)
		{
			extendFeedback(
				"ERROR: Please don't use operators (+, -, *, /, %%, !, =, =, &, |) in name of database."
			);

			return;
		}


		/* Opening database.tosbit with safety for NULL file descriptor. */

		fptr = fopen("data/databases.tosbit", "r+");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Database information for \"%s\" not found!", database);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Writing name of database in database.tosbit, if a new database is made (no overwriting). */

		fseek(fptr, 0, SEEK_END);
		if (!newFile(fptr)) {fputc('\n', fptr);}
		fputs(database, fptr);
		for (int i=0; i<(DATABASE_MAX_LENGTH-1)-strlen(database); i++) {fputc(' ', fptr);}


		/* Safely closing the file descriptor. */

		fclose(fptr);


		/* Opening metadata.tosbit with safety for NULL file descriptor. */

		fptr = fopen("data/metadata.tosbit", "r+");
		if (fptr==NULL) {extendFeedback("ERROR: Data metadata not found!"); return;}


		/* Checking if database's name if larger than existing tables/header. */

		for (int i=0; i<2; i++) {c = fgetc(fptr); if (c!=' ') {metaBuff[i] = c;}}

		if ((int)strlen(database)>atoi(metaBuff))
			{fseek(fptr, 0, SEEK_SET); fputs(itoa((int)strlen(database), ascii), fptr);}


		/* Safely closing the file descriptor. */

		fclose(fptr);
	}



	/* If new database is made, or if an exisiting database is overwritten. */

	if (write==TRUE)
	{
		/* Making table's folder directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "mkdir data/%s", database);
		system(directory);


		/* Creating tables.tosbit */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "touch data/%s/tables.tosbit", database);
		system(directory);


		/* Opening db_name/metadata.tosbit in write & read mode. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/metadata.tosbit", database);


		/* Having safety for NULL file descriptor. */

		fptr = fopen(directory, "w+");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through data/%s!", database);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Writing default configurations to metadata.tosbit (required further too) */

		fputs("6 ", fptr);


		/* Safely closing both the file descriptors. */

		fclose(fptr);


		/* Displaying message for successful database creation. */

		extendFeedback("OK: Database created successfully!");
	}
}










/* Deleting a table. */

void deleteTable(int msg)
{
	/* Initializations */

	char c;
	int counter = 0;
	int match = TRUE;


	/* Checking if table exists or not. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); return;}
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);
	}
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
	{
		/* Removing the table related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);
		system(directory);


		/* Erasing name from list of all available tables. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.tosbit", database);


		/* Opening file with NULL safety for file descriptor. */

		fptr = fopen(directory, "r+");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Table information for \"%s\" not found!", database);
			extendFeedback(feedbackBuffer);

			return;
		}

		

		/* Searching for table's name in tables.tosbit */

		for (int i=0; i<strlen(table); i++)
		{
			c = fgetc(fptr); counter++;

			if (table[counter-1]==c) {continue;}
			else if (table[counter-1]!=c)
			{
				fseek(fptr, (TABLE_MAX_LENGTH-1)-counter, SEEK_CUR);
				c = fgetc(fptr);

				if (c=='\n') {counter = 0; i = -1; continue;}
				else if (reachedEOF(fptr)) {match = FALSE; break;}
			}
		}


		if (match==TRUE)
		{
			c = fgetc(fptr);

			if (c==' ' || c=='\n' || reachedEOF(fptr))
			{
				fseek(fptr, -(counter+1), SEEK_CUR); fputc('\t', fptr);
			}
			else {match = FALSE;}
		}



		/* Giving final feedback (table deleter OR table not found). */

		if ((match==FALSE)&&(msg==TRUE))
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" found!", table);
			extendFeedback(feedbackBuffer);
		}
		else if ((match==TRUE)&&(msg==TRUE)) {extendFeedback("OK: Table deleted successfully!");}


		/* Closing file descriptor to make changes to file (avoiding fflush()). */

		fclose(fptr);
	}
}










/* Deleting a database. */

void deleteDb(int msg)
{
	/* Initializations */

	char c;
	int counter = 0;
	int match = TRUE;


	/* Checking if table exists or not. */

	if (checkDbExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", database);
		extendFeedback(feedbackBuffer);
	}
	else if (checkDbExistence(FALSE)==TRUE)
	{
		/* Removing the database related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s", database);
		system(directory);


		/* Opening file with NULL safety for file descriptor. */

		fptr = fopen("data/databases.tosbit", "r+");
		if (fptr==NULL) {extendFeedback("ERROR: Database information not found!"); return;}

		

		/* Searching for database's name in tables.tosbit */

		for (int i=0; i<strlen(database); i++)
		{
			c = fgetc(fptr); counter++;

			if (database[counter-1]==c) {continue;}
			else if (database[counter-1]!=c)
			{
				fseek(fptr, (DATABASE_MAX_LENGTH-1)-counter, SEEK_CUR);
				c = fgetc(fptr);

				if (c=='\n') {counter = 0; i = -1; continue;}
				else if (reachedEOF(fptr)) {match = FALSE; break;}
			}
		}


		if (match==TRUE)
		{
			c = fgetc(fptr);

			if (c==' ' || c=='\n' || reachedEOF(fptr))
			{
				fseek(fptr, -(counter+1), SEEK_CUR); fputc('\t', fptr);
			}
			else {match = FALSE;}
		}



		/* Giving final feedback (database deleter OR database not found). */

		if ((match==FALSE)&&(msg==TRUE))
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No database named \"%s\" found!", database);
			extendFeedback(feedbackBuffer);
		}
		else if ((match==TRUE)&&(msg==TRUE)) {extendFeedback("OK: Database deleted successfully!");}


		/* Closing file descriptor to make changes to file (avoiding fflush()). */

		fclose(fptr);
	}
}





/* Clears any requested table (clears of all data it holds). */

void clearTable()
{
	/* Checking existence status of the table. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!");}
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);
	}
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
	{
		/* Formatting 'directory' to open rows.tosbit in write mode. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.tosbit", database, table);


		/* Opening rows.tosbit with NULL safe file descriptor. */

		fptr = fopen(directory, "w");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Removing all zip files. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm data/%s/%s/*.xz", database, table);
		system(directory);


		/* Safely closing the file descriptor. */

		fclose(fptr);


		/* Acknowledging user for successful operation. */

		extendFeedback("OK: Table cleared successfully!");
	}
}





/* Clear all the tables present in a database. */

void clearDb()
{
	/* Checking existence of database. */

	if (checkDbExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No database named \"%s\" exists!", database);
		extendFeedback(feedbackBuffer);
	}
	else if (checkDbExistence(FALSE)==TRUE)
	{
		/* Removing whole database directory & recreating new one (with tables.tosbit). */

		clearEntity("directory");

		snprintf(
			directory, sizeof(directory),
			"rm -rf data/%s && mkdir data/%s && touch data/%s/tables.tosbit",
			database, database, database
		);

		system(directory);


		/* Formatting 'directory' to open metadata.tosbit */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/metadata.tosbit", database);


		/* Opening tables.tosbit with NULL safety for file descriptor. */

		fopen(directory, "w");

		if (fptr==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
			extendFeedback(feedbackBuffer);

			return;
		}


		/* Writing defualt metadata to metadata.tosbit */

		fputs("6 ", fptr);


		/* Safely closing file descriptor. */

		fclose(fptr);


		/* Acknowledging user for successful operation. */

		extendFeedback("OK: Database cleared successfully!");
	}
}










/* Checking if unique value exists or not. (UNTESTED ON UNIQUE KEYS) */
// ULTIMATE THING TO REPAIR/DEBUG
int checkUnique(char value[], int currArg, int totalArg)
{
	int invCount=0;
	char value2[strlen(value)];
	char c='$', c2='$';


	fseek(fptr2, 14, SEEK_SET);

	while (!reachedEOF(fptr2))
	{
		memset(value2, 0, strlen(value)*sizeof(char));
		invCount = 0;

		while (invCount!=((currArg-1)*4)+3) {c2 = c; c = fgetc(fptr2); if(c=='\"') {invCount++;}}
		do {c2 = c; c = fgetc(fptr2); value2[strlen(value2)] = c;} while (c!='\"');

		if (!strcmp(value,value2)) {return FALSE;}

		while (invCount!=totalArg*4) {c2 = c; c = fgetc(fptr2); if(c=='\"') {invCount++;}}
		invCount = 0;
		fseek(fptr2, 4, SEEK_CUR);

		c2 = c; c = fgetc(fptr2);

		if (c==',') {fseek(fptr2, 4, SEEK_CUR); continue;}
		else if (c=='\n') {return TRUE;}
		else {extendFeedback("ERROR: rows.tosbit file for current table is corrupted!"); return TRUE;}
	}
}










/* Data type parsing & validating automaton. */

int typeParser()
{
	/* Initializations */

	int status = TRUE;
	char c3 = '$';
	char pipedBuff[257] = {0}, shell_cmd[513] = {0};

	FILE *media=NULL;


	/* int: Integers */

	if (!strcmp(dataType,"int"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 3); breakValue(&state2, 3, &breaker2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "0123456789 ", "1,1,1,1,1,1,1,1,1,1,2", &state2, 3); breakValue(&state2, 3, &breaker2); appendState(&state2, 1, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 4, &breaker2); break;
				case 2: changeState(value[i], " ", "2", &state2, 3); breakValue(&state2, 3, &breaker2); break;
			}


			/* Breaking prematurely from parsing rest of 'value' if reaching dump state. */

			if (breaker2==TRUE) {breaker2 = FALSE; break;}
		}



		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);



		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Argument passed as integer is blank!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 1: state2 = 0; status = TRUE; break;
			case 2: state2 = 0; status = TRUE; break;

			case 3: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) An integer argument is expected!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 4: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Integer value passed exceeds 32 digits!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;
		}


		/* Resetting global variables to avoid errors. */

		state2 = 0; valid = TRUE;
	}





	/* string: String */

	else if (!strcmp(dataType,"string"))
	{
		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);

		if (strlen(pureValue)>VALUE_MAX_LENGTH-1)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) String value passed exceeds 32 digits!", pureValue);
			extendFeedback(feedbackBuffer);

			status = FALSE;
		}
	}





	/* float: Floating point decimals */

	else if (!strcmp(dataType,"float"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 5); breakValue(&state2, 5, &breaker2); appendState(&state2, 1, pureValue, value[i]); break; // Debug this headache, man...
				case 1: changeState(value[i], "0123456789.", "1,1,1,1,1,1,1,1,1,1,2", &state2, 5); breakValue(&state2, 5, &breaker2); appendState(&state2, 1, pureValue, value[i]); appendState(&state2, 2, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &breaker2); break;
				case 2: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &breaker2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &breaker2); break;
				case 3: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &breaker2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &breaker2); break;
				case 4: changeState(value[i], " ", "4", &state2, 5); breakValue(&state2, 5, &breaker2); appendState(&state2, 1, pureValue, value[i]); break;
			}


			/* Breaking prematurely from parsing rest of 'value' if reaching dump state. */

			if (breaker2==TRUE) {breaker2 = FALSE; break;}
		}



		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);



		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Argument passed as float is blank!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 1: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Float has no decimal point!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 2: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) No number written after decimal point!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 3: state2 = 0; status = TRUE; break;
			case 4: state2 = 0; status = TRUE; break;

			case 5: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Supposed float argument is not float!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 6: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Float value passed exceeds 32 digits!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;
		}


		/* Resetting global variables to avoid errors. */

		state2 = 0; valid = TRUE;
	}





	/* bool: Boolean */

	else if (!strcmp(dataType,"bool"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " ft", "0,1,6", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "a", "2", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 2, pureValue, value[i]); break;
				case 2: changeState(value[i], "l", "3", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 3, pureValue, value[i]); break;
				case 3: changeState(value[i], "s", "4", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 4, pureValue, value[i]); break;
				case 4: changeState(value[i], "e", "5", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 5, pureValue, value[i]); break;
				case 5: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &breaker2); break;
				case 6: changeState(value[i], "r", "7", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 7, pureValue, value[i]); break;
				case 7: changeState(value[i], "u", "8", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 8, pureValue, value[i]); break;
				case 8: changeState(value[i], "e", "9", &state2, 11); breakValue(&state2, 11, &breaker2); appendState(&state2, 9, pureValue, value[i]); break;
				case 9: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &breaker2); break;
				case 10: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &breaker2); break;
			}


			/* Breaking prematurely from parsing rest of 'value' if reaching dump state. */

			if (breaker2==TRUE) {breaker2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Argument passed as boolean is blank!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 1: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"false\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 2: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"false\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 3: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"false\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 4: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"false\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 5: state2 = 0; status = TRUE; break;

			case 6: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"true\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 7: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"true\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 8: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Did you meant \"true\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;

			case 9: state2 = 0; status = TRUE; break;
			case 10: state2 = 0; status = TRUE; break;

			case 11: clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) Argument is neither \"true\" or \"false\"!", pureValue);
					extendFeedback(feedbackBuffer);
					status = FALSE; break;
		}


		/* Resetting global variables to avoid errors. */

		state2 = 0; valid = TRUE;
	}





	/* media: Media files (WARNING - To be put with file extension). */

	else if (!strcmp(dataType,"media"))
	{
		/* Removing whitespaces. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);


		/* Taking path of target file. */

		if (serverMode==TRUE)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "Enter path for \"%s\": ", attribute);
			extendFeedback(feedbackBuffer);
		}
		else if (serverMode==FALSE)
		{
			printf("Enter path for \"%s\": ", attribute);
		}


		/* Getting the input from user for file's path. */

		clearEntity("directory"); fgets(directory, sizeof(directory), stdin);
		newline_remover(directory); extendFeedback("\n");

		

		/*

		Checking existence of media file:

		media -> FD to check media file's existence.
		directory -> Path to media file.
		shell_cmd -> Complete shell command to copy target file.

		Path: {PASTE_YOUR_PATH_HERE}

		*/



		/* Trying to open the target file to check its existence (with NULL safety). */

		media = fopen(directory, "r");

		if (media==NULL)
		{
			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: (%s) No such file exists!", directory);
			extendFeedback(feedbackBuffer);

			status = FALSE; return FALSE;
		}


		/* Acknowledging user when file is being compressed. */

		fclose(media);
		extendFeedback("STAT: File is being compressed...\n");


		/* Compressing the file. */

		snprintf(shell_cmd, sizeof(shell_cmd), "xz -k %s", directory);
		system(shell_cmd);


		/* Copying the zip file. */

		memset(shell_cmd, 0, sizeof(shell_cmd));
		snprintf(shell_cmd, sizeof(shell_cmd), "cp %s.xz data/%s/%s/%s.xz", directory, database, table, pureValue);
		system(shell_cmd);


		/* Deleting the zip copy at user's directory. */

		memset(shell_cmd, 0, sizeof(shell_cmd));
		snprintf(shell_cmd, sizeof(shell_cmd), "rm %s.xz", directory);
		system(shell_cmd);


		/* Comparing actual size with compression rate. */

		memset(shell_cmd, 0, sizeof(shell_cmd));
		snprintf(shell_cmd, sizeof(shell_cmd), "du -h %s", directory);


		/* Fetching early size of file through process piping. */

		media = popen(shell_cmd, "r");

		do {
			c3 = fgetc(media);

			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c3);
			extendFeedback(feedbackBuffer);
		}
		while (c3!='\t'); extendFeedback(" ->\t");


		/* Safely closing file descriptor. */

		pclose(media);


		/* Formatting 'shell_cmd' to know compressed size of the file. */

		memset(shell_cmd, 0, sizeof(shell_cmd));
		snprintf(shell_cmd, sizeof(shell_cmd), "du -h data/%s/%s/%s.xz", database, table, pureValue);


		/* Fetching later size through process piping. */

		media = popen(shell_cmd, "r");

		do {
			c3 = fgetc(media);

			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c3);
			extendFeedback(feedbackBuffer);
		}
		while (c3!='\t'); extendFeedback("\n");
		

		/* Safely closing file descriptor. */

		pclose(media);


		/* Setting status as true for error free type parsing. */

		status = TRUE;
	}


	/* Error handling safety for unknown bug (just for check purposes). */

	else {extendFeedback("ERROR: Not matching any data type!"); status = FALSE;}


	/* Returning status, telling if type parsing was error free or not. */

	return status;
}










/* Pushing row into a table. */

void pushRow()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int commaCount=0, buffIndex=0, totalArg, currArg=0;
	int actualAttributes = 1;
	int largestValue;



	/* Checking if database opened or not with existence of the tables. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); return;}
	else if (checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		return;
	}



	/* Queue structure to handle attributes. */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to handle data types. */

	Queue dataTypeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to handle values. */

	Queue valueQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};



	/* Formatting 'directory' to open details.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);


	/* Opening details.tosbit with NULL safety. */

	fptr = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
		extendFeedback(feedbackBuffer);
	}


	/* Formatting 'directory' to open rows.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.tosbit", database, table);


	/* Opening rows.tosbit with NULL safety. */

	fptr2 = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
		extendFeedback(feedbackBuffer);
	}


	/* Checking number of argument passed. */

	for (int i=0; i<strlen(buffer); i++) {if(buffer[i]==',') {commaCount++;}}
	totalArg = commaCount + 1;


	/* Checking number or attributes the table has. */

	while (!reachedEOF(fptr))
	{
		fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)+1+(DATA_TYPE_MAX_LENGTH-1)+1+(KEY_MAX_LENGTH-1)+1+2, SEEK_CUR);

		c = fgetc(fptr);
		if (c=='\n') {actualAttributes++; continue;}
	}


	/* Giving feedback as per number of arguments passed. */

	if (totalArg<actualAttributes) {extendFeedback("ERROR: Very few arguments passed!"); fclose(fptr); fclose(fptr2); return;}
	else if (totalArg>actualAttributes) {extendFeedback("ERROR: Too many arguments passed!"); fclose(fptr); fclose(fptr2); return;}


	
	/* Moving cursor back to start of file. */

	fseek(fptr, 0, SEEK_SET);


	/* Verifying data types of passed arguments. */

	for (int i=1; i<=actualAttributes; i++)
	{
		/* Clearing all repitatively used buffers. */

		clearEntity("attribute"); clearEntity("dataType"); clearEntity("key"); clearEntity("value");


		/* Counting number of arguments. */

		currArg++;


		/* Fetching current value/argument from buffer. */

		for (int i=buffIndex; i<strlen(buffer); i++)
		{
			if (buffer[i]==',') {buffIndex = i + 1; break;}
			else {value[strlen(value)] = buffer[i];}
		}


		/* Fetching the name of first/next attribute from details.tosbit */

		c = fgetc(fptr);
		do {attribute[strlen(attribute)] = c; c = fgetc(fptr);} while (c!=' ' && c!=',');
		fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)-strlen(attribute), SEEK_CUR);


		/* Fetching the name of first/next data type from details.tosbit */

		c = fgetc(fptr);
		do {dataType[strlen(dataType)] = c; c = fgetc(fptr);} while (c!=' ' && c!=',');
		fseek(fptr, (DATA_TYPE_MAX_LENGTH-1)-strlen(dataType), SEEK_CUR);


		/* Fetching the name of first/next key from details.tosbit */

		c = fgetc(fptr);
		do {key[strlen(key)] = c; c = fgetc(fptr);} while (c!=' ' && c!=',');
		fseek(fptr, (KEY_MAX_LENGTH-1)-strlen(key), SEEK_CUR);


		/* Checking if the passed argument is holding data type constraints. */

		if (typeParser()==FALSE) {fclose(fptr); fclose(fptr2); return;}


		/* Fetching data from details.tosbit */

		memset(metaBuff, 0, sizeof(metaBuff));

		for (int j=0; j<2; j++)
		{
			c = fgetc(fptr);
			if (c!=' ') {metaBuff[j] = c;}
		}


		/* Making changes to details.tosbit (if required) */

		if ((int)strlen(pureValue)>atoi(metaBuff))
		{
			fseek(fptr, -2, SEEK_CUR);
			fputs(itoa((int)strlen(pureValue),ascii), fptr);

			if (strlen(pureValue)<10) {fseek(fptr, 1, SEEK_CUR);}
		}


		/* Checking duplication insertion attempts for unique attributes. */

		// if (!strcmp(key,"unique"))		// UNDER REPAIR/ MODIFICATION/ DEBUGGING...
		// {
		// 	if (checkUnique(value, currArg, totalArg)==FALSE)
		// 	{
		// 		printf("ERROR: Duplicate for unique key \"%s\"!", attribute); return;
		// 	}
		// }


		/* Skipping the '\n' for non-last arguments in file. */

		if (i!=actualAttributes) {fseek(fptr, 1, SEEK_CUR);}


		/* Queueing attribute properties to respective queues. */

		attributeQueue.queue(&attributeQueue, attribute);
		dataTypeQueue.queue(&dataTypeQueue, dataType);
		valueQueue.queue(&valueQueue, pureValue);
	}


	/* Safely closing file descriptor used for viewing details. */

	fclose(fptr);



	/* Inserting values. */

	if (!newFile(fptr2)) {fseek(fptr2, 0, SEEK_END); fputc('\n', fptr2);}


	for (int i=0; i<totalArg; i++)
	{
		/* Inserting arguments to rows.tosbit, one-by-one from queue. */

		fputs(valueQueue.getValue(&valueQueue,i), fptr2);

		if (!strcmp(dataTypeQueue.getValue(&dataTypeQueue,i), "bool"))
		{
			for (int j=0; j<5-strlen(valueQueue.getValue(&valueQueue,i)); j++)
			{
				fputc(' ', fptr2);
			}
		}
		else
		{
			for (int j=0; j<(VALUE_MAX_LENGTH-1)-strlen(valueQueue.getValue(&valueQueue,i)); j++)
			{
				fputc(' ', fptr2);
			}
		}


		/* For non-last value, inserting comma. */

		if (i!=totalArg-1) {fputc(',', fptr2);}
	}


	/* Safely closing file descriptor. */

	fclose(fptr2);


	/* Clearing queues from memory. */
	
	attributeQueue.clear(&attributeQueue);
	dataTypeQueue.clear(&dataTypeQueue);
	valueQueue.clear(&dataTypeQueue);


	/* Acknowledging user for successful push operation. */

	extendFeedback("OK: Row pushed successfully!");
}










/* Parses the selection arguments & provides feedback on its integrity. */

void selectionParser()
{
	/* Queue structure to handle attributes. */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};



	/* Checking if database opened or not with existence of the tables. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); return;}
	else if (checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		return;
	}



	/* DFA-based parser to extract all attribute names. */

	for (int i=0; i<strlen(buffer); i++)
	{
		switch (state2)
		{
			case 0: clearEntity("attribute"); changeState(buffer[i], " @", "0,1", &state2, 3); appendState(&state2, 3, attribute, buffer[i]); break;
			case 1: changeState(buffer[i], " ", "1", &state2, 2); breakValue(&state2, 2, &breaker2); break;
			case 3: changeState(buffer[i], " ,", "4,5", &state2, 3); appendState(&state2, 3, attribute, buffer[i]); limitChecker(attribute, (ATTRIBUTE_MAX_LENGTH-1), &state2, 6, &breaker2); break;
			case 4: changeState(buffer[i], " ,", "4,5", &state2, 7); breakValue(&state2, 2, &breaker2); break;
			case 5: if (strlen(attribute)>0) {attributeQueue.queue(&attributeQueue, attribute);} clearEntity("attribute"); changeState(buffer[i], " ", "5", &state2, 3); appendState(&state2, 3, attribute, buffer[i]);break;
		}


		/* Prematurely breaking from loop if DFA reaches dump state. */

		if (breaker2==TRUE) {breaker2 = FALSE; break;}
	}

	
	/* Appending the one-and-only or the last attribute in buffer to queue. */

	if (state2==3 || state2==4) {attributeQueue.queue(&attributeQueue, attribute);}



	/* Taking action as per the final stop-state. */

	switch (state2)
	{
		case 0: extendFeedback("ERROR: No column name passed as argument!"); break;
		case 1: allRows(); break;
		case 2: extendFeedback("ERROR: Syntax error when requesting for all columns!"); break;
		case 3: extendFeedback("OK: Columns requsted manually."); break;
		case 4: extendFeedback("OK: Columns requsted manually."); break;
		case 5: extendFeedback("ERROR: Check position of commas!"); break;
		case 6: extendFeedback("ERROR: Attribute name limit exceeded!"); break;
		case 7: extendFeedback("ERROR: No comma among names of columns!"); break;
	}


	/* Resetting values to avoid future errors. */

	state2 = 0; valid = TRUE;
}










/* Parser to check integrity of conditional syntax (after WHERE). */

void allRows()
{
	/* Initializations */

	char c;
	char largestAttributeS[2] = {0}, dataTypeS[DATA_TYPE_MAX_LENGTH] = {0};
	int largestAttributeN = 0;
	int charsPrinted = 0, charsRead = 0;
	int rowLength = 0, rowCount = 0;
	int sizeCounter = 0, stringSpaces = 0;


	/* Queue structure to handle data type of each table attribute. */

	Queue dataTypeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to handle size of each table attribute. */

	Queue sizeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to compare size of each table attribute. */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to compare size of each table attribute. */

	Queue attributeSizeNQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};



	/* Checking if database opened or not with existence of the tables. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); return;}
	else if (checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		return;
	}



	/* Formatting 'directory' to open details.tosbit in 'r' mode. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);


	/* Opening details.tosbit with NULL safety. */

	fptr = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* Fetching data type & length of largest names for each attribute. */

	while (!reachedEOF(fptr))
	{
		/* Moving file descriptor to fetch largest value of an attribute. */

		fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)+1, SEEK_CUR);


		/* Fetching the largest value of an attribute. */

		memset(dataTypeS, 0, sizeof(dataTypeS));	// Running 2-bytes ahead.

		charsRead = 0; c = fgetc(fptr);
		while (c!=' ' && c!=',') {dataTypeS[strlen(dataTypeS)] = c; c = fgetc(fptr); charsRead++;}


		/* Queueing the name of an attribute to 'dataTypeQueue'. */

		dataTypeQueue.queue(&dataTypeQueue, dataTypeS);



		/* Moving file descriptor to fetch largest value of an attribute. */
// ANALYZE WHY IT WORKS WITHOUT EXTRA 1 BYTE MOVEMENT!/////////////////////////////////////////////
		fseek(fptr, (DATA_TYPE_MAX_LENGTH-1)+1+(KEY_MAX_LENGTH-1)+1-charsRead-1, SEEK_CUR);


		/* Fetching the largest value of an attribute. */

		memset(largestAttributeS, 0, sizeof(largestAttributeS));

		for (int i=0; i<2; i++)
		{
			c = fgetc(fptr);
			if (c!=' ') {largestAttributeS[i] = c;}
		}


		/* Queueing the largest value of an attribute to 'sizeQueue'. */

		sizeQueue.queue(&sizeQueue, largestAttributeS);


		/* Making the FD ready to repeat this process for the next attribute. */

		fseek(fptr, 1, SEEK_CUR);
	}



	/* Filling 0 to as defualt to 'attributeSizeNQueue'. */

	for (int i=0; i<sizeQueue.n; i++) {attributeSizeNQueue.queue(&attributeSizeNQueue, "0");}



	/* Printing upper ribbon of console-table's head. */

	for (int i=0; i<sizeQueue.n; i++)
	{
		extendFeedback("+"); for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i)); j++) {extendFeedback("-");}
	}
	extendFeedback("+\n");



	/* Moving FD to start of the file to print attributes now. */

	fseek(fptr, 0, SEEK_SET);


	for (int i=0; i<sizeQueue.n; i++)
	{
		/* Printing the name of attributes on top bar. */

		clearEntity("attribute"); charsPrinted = 0; extendFeedback("|"); c = fgetc(fptr);

		while (c!=' ' && c!=',')
		{
			attribute[strlen(attribute)] = c;

			clearEntity("feedbackBuffer");
			snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
			extendFeedback(feedbackBuffer);

			charsPrinted++;
			c = fgetc(fptr);
		}


		/* Queuing name of the attribute name to its queue. */

		attributeQueue.queue(&attributeQueue, attribute);


		/* Printing spaces to maintain structure of console-table. */

		for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i))-charsPrinted; j++) {extendFeedback(" ");}


		/* Moving FD backward by one byte, as it read a character further for check. */

		fseek(fptr, -1, SEEK_CUR);


		/* Moving FD to end of line (to '\n' or EOF). */

		fseek(fptr,
			(ATTRIBUTE_MAX_LENGTH-1)+1+(DATA_TYPE_MAX_LENGTH-1)+1+(KEY_MAX_LENGTH-1)+1+2-charsPrinted+1,
			SEEK_CUR
		);
	}
	extendFeedback("|\n");



	/* Printing lower ribbon of console-table's head. */

	for (int i=0; i<sizeQueue.n; i++)
	{
		extendFeedback("+");
		for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i)); j++) {extendFeedback("-");}
	}
	extendFeedback("+\n");



	/* Summing length of a row (including commas). */

	for (int i=0; i<sizeQueue.n; i++) {rowLength += atoi(sizeQueue.getValue(&sizeQueue, i));}
	rowLength += (sizeQueue.n)-1;		// commas = attributes - 1


	/* Formatting 'directory' to open rows.tosbit in 'r' mode. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.tosbit", database, table);


	/* Opening rows.tosbit with NULL safety. */

	fptr2 = fopen(directory, "r");

	if (fptr2==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* Reading rows from rows.data */

	while (!reachedEOF(fptr2))
	{
		/* Skipping deleted rows (those starting with '\t'). */

		c = fgetc(fptr2);
		if (c=='\t') {fseek(fptr2, rowLength+1, SEEK_CUR);}
		else {fseek(fptr2, -1, SEEK_CUR);}


		/* Printing the row (including spaces in file). */

		for (int i=0; i<sizeQueue.n; i++)
		{
			/* Initializing certain values & printing default designs. */

			charsPrinted = 0; extendFeedback("|");
			

			/* For boolean type attributes. */

			if (!strcmp(dataTypeQueue.getValue(&dataTypeQueue, i),"bool"))
			{
				/* Printing attribute's value to screen. */

				for (int j=0; j<5; j++)
				{
					c = fgetc(fptr2);

					clearEntity("feedbackBuffer");
					snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
					extendFeedback(feedbackBuffer);

					charsPrinted++;
				}


				/* Covering rest of the space, with space. */

				for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i))-charsPrinted; j++)
				{
					extendFeedback(" ");
				}


				/* Skipping remaining spaces with comma or endline character. */

				fseek(fptr2, 5-charsPrinted+1, SEEK_CUR);
			}


			/* For other type of attributes. */

			else
			{
				/* Printing attribute's value to screen. */

				c = fgetc(fptr2);


				for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i)); j++)
				{
					stringSpaces = 0;


					/* While space hasn't appeared. */

					while (c!=' ')
					{
						clearEntity("feedbackBuffer");
						snprintf(feedbackBuffer, sizeof(feedbackBuffer), "%c", c);
						extendFeedback(feedbackBuffer);

						charsPrinted++; c = fgetc(fptr2); j++;
					}


					/* While non-space hasn't been read or max characters not read. */

					while (c==' ' && j<atoi(sizeQueue.getValue(&sizeQueue, i)))
					{
						stringSpaces++;
						extendFeedback(" "); c = fgetc(fptr2);

						j++;
					}


					/* Trying out the all possible combinations. */

					if (c==' ' && j==atoi(sizeQueue.getValue(&sizeQueue, i))) {break;}
					else if (c!=' ' && j<atoi(sizeQueue.getValue(&sizeQueue, i)))
					{
						charsPrinted += stringSpaces;
						j--;
					}
				}



				/* Skipping remaining spaces along with comma or endline character. */
				
				fseek(fptr2, (VALUE_MAX_LENGTH-1)-atoi(sizeQueue.getValue(&sizeQueue, i))+1-1, SEEK_CUR);
			}


			/* Storing the largest encountered attribute length. */

			if (charsPrinted>atoi(attributeSizeNQueue.getValue(&attributeSizeNQueue, i)))
			{
				attributeSizeNQueue.changeAt(&attributeSizeNQueue, i, itoa(charsPrinted, ascii));
			}
		}

		extendFeedback("|\n"); rowCount++;
	}


	/* Printing ribbon of console-table's tail. */

	for (int i=0; i<sizeQueue.n; i++)
	{
		extendFeedback("+"); for (int j=0; j<atoi(sizeQueue.getValue(&sizeQueue, i)); j++) {extendFeedback("-");}
	}
	extendFeedback("+\n");



	/* Bringing FP back to starting of details.tosbit. */

	fseek(fptr, 0, SEEK_SET);


	/* Checking if metadata in details.tosbit needs to be changed. */

	for (int i=0; i<sizeQueue.n; i++)
	{
		/* Moving file descriptor to fetch largest value of an attribute. */

		fseek(
			fptr,
			(ATTRIBUTE_MAX_LENGTH-1)+1+(DATA_TYPE_MAX_LENGTH-1)+1+(KEY_MAX_LENGTH-1)+1,
			SEEK_CUR
		);


		/* Checking the largest value of an attribute. */

		if (
			atoi(attributeSizeNQueue.getValue(&attributeSizeNQueue, i))<atoi(sizeQueue.getValue(&sizeQueue, i)) &&
			atoi(attributeSizeNQueue.getValue(&attributeSizeNQueue, i))>=strlen(attributeQueue.getValue(&attributeQueue, i))
		)
		{
			fputs(attributeSizeNQueue.getValue(&attributeSizeNQueue, i), fptr);

			if (atoi(attributeSizeNQueue.getValue(&attributeSizeNQueue, i))<10) {fputc(' ', fptr);}
			fseek(fptr, 1, SEEK_CUR);
		}
		else {fseek(fptr, 3, SEEK_CUR);}
	}



	/* Printing stats information. */

	clearEntity("feedbackBuffer");
	snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: Total %d rows found.", rowCount);
	extendFeedback(feedbackBuffer);



	/* Safely closing file descriptor. */

	fclose(fptr); fclose(fptr2);


	/* Clearing queues. */

	sizeQueue.clear(&sizeQueue);
	dataTypeQueue.clear(&dataTypeQueue);
	attributeQueue.clear(&attributeQueue);
	attributeSizeNQueue.clear(&attributeSizeNQueue);
}










/* Update parser parses & validates the first buffer in UPDATE command. */

void updateParser()
{
	/* Declaration of variables. */

	int prevState;



	/* Queue structure to handle attribute arguments. */

	Queue argumentQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	/* Queue structure to handle values. */

	Queue valueQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};



	/* DFA-based parser to extract all attribute names. */

	for (int i=0; i<strlen(buffer); i++)
	{
		/* Storing previous state. */

		prevState = state2;


		/* Automaton switch cases. */

		switch (state2)
		{
			case 0: clearEntity("attribute"); changeState(buffer[i], " ", "0", &state2, 1); appendState(&state2, 1, attribute, buffer[i]); break;
			case 1: changeState(buffer[i], " =", "2,3", &state2, 1); appendState(&state2, 1, attribute, buffer[i]); limitChecker(attribute, (ATTRIBUTE_MAX_LENGTH-1), &state2, 8, &breaker2); break;
			case 2: changeState(buffer[i], " =", "2,3", &state2, 6); breakValue(&state, 6, &breaker); break;
			case 3: clearEntity("value"); changeState(buffer[i], " ", "3", &state2, 4); appendState(&state2, 4, value, buffer[i]); break;
			case 4: changeState(buffer[i], ",", "0", &state2, 4); appendState(&state2, 4, value, buffer[i]); limitChecker(value, (VALUE_MAX_LENGTH-1), &state2, 9, &breaker2); break;
			//case 5: changeState(buffer[i], " ,", "5,0", &state2, 7); breakValue(&state, 7, &breaker); break;
		}


		/* Queueing attribute or value at right state transition. */

		if (prevState==1 && (state2==2 || state2==3)) {argumentQueue.queue(&argumentQueue, attribute);}
		else if (prevState==4 && (state2==5 || state2==0))
		{
			memset(pureValue, 0, sizeof(pureValue));

			spaceRemover(value, pureValue, VALUE_MAX_LENGTH);
			valueQueue.queue(&valueQueue, pureValue);
		}


		/* Prematurely breaking from loop if DFA reaches dump state. */

		if (breaker2==TRUE) {breaker2 = FALSE; break;}
	}


	/* If last state was 4, queue the last value. */

	if (state2==4)
	{
		memset(pureValue, 0, sizeof(pureValue));

		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);
		valueQueue.queue(&valueQueue, pureValue);
	}



	/* Taking action as per the final stop-state. */

	switch (state2)
	{
		case 0: extendFeedback("ERROR: Pass atleast one argument & remove extra comma!"); break;
		case 1: extendFeedback("ERROR: Please define value to update attribute with."); break;
		case 2: extendFeedback("ERROR: Please define value to update attribute with."); break;
		case 3: extendFeedback("ERROR: Please define value to update attribute with."); break;
		case 4: state2 = 0; updateAll(&argumentQueue, &valueQueue); break;
		//case 5: state2 = 0; updateAll(&argumentQueue, &valueQueue); break;
		case 6: extendFeedback("ERROR: Check for missing assignment operator!"); break;
		case 7: extendFeedback("ERROR: A comma is expected after each assignment!"); break;
		case 8: extendFeedback("ERROR: Attribute length limit exceeded!"); break;
		case 9: extendFeedback("ERROR: Value length limit exceeded!"); break;
	}


	/* Clearing queues. */

	argumentQueue.clear(&argumentQueue);
	valueQueue.clear(&valueQueue);


	/* Resetting values to avoid future errors. */

	state2 = 0; valid = TRUE;
}










/* Updating all rows for a given value for each. */

void updateAll(struct Queue *argumentQueue, struct Queue *valueQueue)
{
	/* Declarations */

	char c;
	char metaBuff[2] = {0}, str[33] = {0};
	int charsRead, charsPrinted;
	int rowLength = 0, totalRows = 0;


	/* Structure objects. */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};

	Queue dataTypeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};

	Queue keyQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};

	Queue largestValueQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};

	Queue markQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};



	/* Checking if database opened or not with existence of the tables. */

	if (checkDbExistence(FALSE)==FALSE) {extendFeedback("ERROR: No database opened yet!"); return;}
	else if (checkTableExistence(FALSE)==FALSE)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: No table named \"%s\" exists!", table);
		extendFeedback(feedbackBuffer);

		return;
	}



	/* Formatting directory to open details.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);


	/* Opening details.tosbit with NULL safety. */

	fptr = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* While EOF not reached in details.tosbit (extracting data) */

	while (!reachedEOF(fptr))
	{
		/* Extracting attribute. */

		clearEntity("attribute"); charsRead = 0; c = fgetc(fptr);
		while (c!=' ' && c!=',') {attribute[strlen(attribute)] = c; c = fgetc(fptr); charsRead++;}
		attributeQueue.queue(&attributeQueue, attribute);


		/* Marking with 'yes' if this attribute was requested, else 'no'. */

		if (argumentQueue->getIndex(argumentQueue, attribute)!=-1) {markQueue.queue(&markQueue, "yes");}
		else if (argumentQueue->getIndex(argumentQueue, attribute)==-1) {markQueue.queue(&markQueue, "no");}


		/* Moving FD forward to read the data type for same attribute. */

		fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)-charsRead+1-1, SEEK_CUR);


		/* Extracting data type. */

		clearEntity("dataType"); charsRead = 0; c = fgetc(fptr);
		while (c!=' ' && c!=',') {dataType[strlen(dataType)] = c; c = fgetc(fptr); charsRead++;}
		dataTypeQueue.queue(&dataTypeQueue, dataType);


		/* Moving FD forward to read the key for same attribute. */

		fseek(fptr, (DATA_TYPE_MAX_LENGTH-1)-charsRead+1-1, SEEK_CUR);


		/* Extracting key. */

		clearEntity("key"); charsRead = 0; c = fgetc(fptr);
		while (c!=' ' && c!=',') {key[strlen(key)] = c; c = fgetc(fptr); charsRead++;}
		keyQueue.queue(&keyQueue, key);


		/* Moving FD forward to read the largest value for same attribute. */

		fseek(fptr, (KEY_MAX_LENGTH-1)-charsRead+1-1, SEEK_CUR);


		/* Extracting largest values. */

		memset(metaBuff, 0, sizeof(metaBuff));
		charsRead = 0; c = fgetc(fptr);
		while (c!=' ' && c!='\n') {metaBuff[strlen(metaBuff)] = c; c = fgetc(fptr); charsRead++;}
		largestValueQueue.queue(&largestValueQueue, metaBuff);


		/* Moving FD forward to read the next row. */

		fseek(fptr, (2+1)-charsRead-1, SEEK_CUR);
	}



	/* Checking if the arguments passed contained non-existing attributes. */

	for (int i=0; i<argumentQueue->n; i++)
	{
		if (attributeQueue.getIndex(&attributeQueue, argumentQueue->getValue(argumentQueue, i)) == -1)
		{
			clearEntity("feedbackBuffer");
			snprintf(
				feedbackBuffer, sizeof(feedbackBuffer),
				"ERROR: No attribute named \"%s\" exists in table \"%s\"!",
				argumentQueue->getValue(argumentQueue, i), table
			);
			extendFeedback(feedbackBuffer);


			return;
		}
	}



	/* Checking consistencies in the data types & keys of requested attributes. */

	for (int i=0; i<attributeQueue.n; i++)
	{
		/* For safety, using 'str' to access strings in 'markQueue'. */

		memset(str, 0, sizeof(str));
		strcpy(str, markQueue.getValue(&markQueue, i));


		/* Checking only requested attributes in particular. */

		if (!strcmp(str,"yes"))
		{
			/* Fetching the next attribute & value only. */

			clearEntity("dataType"); strcpy(dataType, dataTypeQueue.getValue(&dataTypeQueue, i));
			clearEntity("key"); strcpy(key, keyQueue.getValue(&keyQueue, i));


			/* Value at index of the found argument, referring to attributeQueue & markQueue. */

			clearEntity("value");

			strcpy(
				value,
				valueQueue->getValue(valueQueue, argumentQueue->getIndex(argumentQueue, attributeQueue.getValue(&attributeQueue, i)))
			);


			/* Checking data type & key type. */

			if (!strcmp(key,"unique") || !strcmp(key,"file"))
			{
				extendFeedback("ERROR: Unique & File attributes can't change!");
				return;
			}
			if (typeParser()==FALSE) {return;}
		}
	}



	/* Calculating row length. */

	rowLength = (ATTRIBUTE_MAX_LENGTH-1+1)+(DATA_TYPE_MAX_LENGTH-1+1)+(KEY_MAX_LENGTH-1+1)+2;


	/* Moving FD to the start of the file. */

	fseek(fptr, 0, SEEK_SET);


	/* Metadata updation in details.tosbit (largest attribute name length). */

	for (int i=0; i<markQueue.n; i++)
	{
		/* Now using 'str' for different purpose, for shortening code length. */

		memset(str, 0, sizeof(str));

		strcpy(str,
			valueQueue->getValue(valueQueue, argumentQueue->getIndex(argumentQueue, attributeQueue.getValue(&attributeQueue, i)))
		);


		/* Making changes in details.tosbit */

		if (!strcmp(markQueue.getValue(&markQueue, i),"yes"))
		{
			if (strlen(str)!=atoi(largestValueQueue.getValue(&largestValueQueue, i)) && strlen(str)>=strlen(attributeQueue.getValue(&attributeQueue, i)))
			{
				fseek(fptr, rowLength-2, SEEK_CUR);
				fputs(itoa((int)strlen(str), ascii), fptr);

				if ((int)strlen(str)<10) {fputc(' ', fptr);}
			}
		}


		/* Skipping whole details for the attribute if not requested for update. */

		else {fseek(fptr, rowLength, SEEK_CUR);}


		/* Skipping the '\n'/going to EOF. */

		fseek(fptr, 1, SEEK_CUR);
	}

	


	/* Closing FD safely for later use in modifying values. */

	fclose(fptr);



	/* Formatting directory to open details.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.tosbit", database, table);


	/* Opening details.tosbit with NULL safety. */

	fptr = fopen(directory, "r+");

	if (fptr==NULL)
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "ERROR: Can't navigate through %s!", directory);
		extendFeedback(feedbackBuffer);

		return;
	}


	/* Returning if the table is empty. */

	if (newFile(fptr))
	{
		clearEntity("feedbackBuffer");
		snprintf(feedbackBuffer, sizeof(feedbackBuffer), "STAT: Table \"%s\" is empty.", table);
		extendFeedback(feedbackBuffer);
	}


	/* Traversing whole table data & modifying it. */

	while (!reachedEOF(fptr))
	{
		/* Counting rows after each endline character. */

		totalRows++;


		for (int i=0; i<markQueue.n; i++)
		{
			/* If modification is required. */

			if (!strcmp(markQueue.getValue(&markQueue, i),"yes"))
			{
				/* Now using 'str' for different purpose, for shortening code length. */

				memset(str, 0, sizeof(str));

				strcpy(str,
					valueQueue->getValue(valueQueue, argumentQueue->getIndex(argumentQueue, attributeQueue.getValue(&attributeQueue, i)))
				);


				/* Writing the new value. */

				fputs(str, fptr);


				/* Writing spaces to file as per its data type (boolean or non-boolean). */

				if (!strcmp(dataTypeQueue.getValue(&dataTypeQueue, i),"bool"))
				{
					for (int j=0; j<5-strlen(str); j++) {fputc(' ', fptr);}
					fseek(fptr, 1, SEEK_CUR);
				}
				else
				{
					for (int j=0; j<(ATTRIBUTE_MAX_LENGTH-1)-strlen(str); j++) {fputc(' ', fptr);}
					fseek(fptr, 1, SEEK_CUR);
				}
			}



			/* If modification isn't required (attribute wasn't requested). */

			else if (!strcmp(markQueue.getValue(&markQueue, i),"no"))
			{
				if (!strcmp(dataTypeQueue.getValue(&dataTypeQueue, i),"bool"))
					{fseek(fptr, 5+1, SEEK_CUR);}

				else {fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)+1, SEEK_CUR);}
			}
		}
	}



	/* Clearing all the local queues (of this function). */

	attributeQueue.clear(&attributeQueue);
	dataTypeQueue.clear(&dataTypeQueue);
	keyQueue.clear(&keyQueue);
	largestValueQueue.clear(&largestValueQueue);


	/* Safely closing file. */

	fclose(fptr); // APPLY CRITICAL WRITES & RESIZING CONSOLE-TABLES TOO...


	/* Acknowledging users about update in query. */

	clearEntity("feedbackBuffer");
	snprintf(feedbackBuffer, sizeof(feedbackBuffer), "OK: Total %d rows updated!", totalRows);
	extendFeedback(feedbackBuffer);
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */