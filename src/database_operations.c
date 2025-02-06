#include "../include/database_operations.h"




















/* Global initializations */

FILE *fptr = NULL;
FILE *fptr2 = NULL;
FILE *cache = NULL;

char command[COMMAND_MAX_LENGTH] = {0};
char database[DATABASE_MAX_LENGTH] = {0};
char table[TABLE_MAX_LENGTH] = {0};
char directory[DIRECTORY_MAX_LENGTH] = {0};
char buffer[BUFFER_MAX_LENGTH] = {0};
char dataType[DATA_TYPE_MAX_LENGTH] = {0};
char attribute[ATTRIBUTE_MAX_LENGTH] = {0};
char key[KEY_MAX_LENGTH] = {0};
char value[VALUE_MAX_LENGTH] = {0};
char pureValue[VALUE_MAX_LENGTH] = {0};

int state = 0;								// Main automaton
int state2 = 0;								// Table attribute automaton
int zero_count = 0;

int brk = FALSE;							// Set TRUE when the syntax goes wrong.
int brk2 = FALSE;
int valid = TRUE;							// Syntax if found wrong, only then invalid.




















/* This function clears a string, identified through entered value of string. */

void clearEntity(char *str)
{
	if (!strcmp(str,"command")) {memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"database")) {memset(database, 0, DATABASE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"table")) {memset(table, 0, TABLE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"directory")) {memset(directory, 0, DIRECTORY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"buffer")) {memset(buffer, 0, BUFFER_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"dataType")) {memset(dataType, 0, DATA_TYPE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"attribute")) {memset(attribute, 0, ATTRIBUTE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"key")) {memset(key, 0, KEY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"value")) {memset(value, 0, VALUE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"pureValue")) {memset(pureValue, 0, VALUE_MAX_LENGTH*sizeof(char));}
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

		printf("ERROR: No database named \"%s\" exists!\n\n", database);
		clearEntity("database");
	}
	else if (fptr==NULL && msg==FALSE) {existence = FALSE;}
	else if (fptr!=NULL && msg==TRUE)
	{
		existence = TRUE;
		printf("STAT: Database %s online!\n\n", database);

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

	if (strlen(database)==0 && msg==TRUE) {printf("ERROR: No database opened yet!\n\n");}
	else if (fptr==NULL && msg==FALSE) {existence = FALSE;}
	else if (fptr==NULL && msg==TRUE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
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
	int charsPrinted = 0, totalAttributes = 0;


	/* Opening metadata.tosbit & giving safety against NULL file descriptor. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/metadata.tosbit", database, table);
	fptr = fopen(directory, "r");

	if (fptr==NULL) {printf("ERROR: Metadata for table \"%s\" not found!\n\n", table); return;}


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


	/* Safely closing file descriptor. */

	fclose(fptr);


	/* Opening details.json & giving safety against NULL file descriptor. */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.tosbit", database, table);
	fptr = fopen(directory, "r");

	if (fptr==NULL) {printf("ERROR: Details for \"%s\" not found!\n\n", table); return;}


	/* Printing upper part of the console-table (the header of the table). */

	printf("+"); for (int i=0; i<largestAttribute; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestDataType; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestKey; i++) {printf("-");} printf("+\n");

	printf("|Attributes"); for (int i=0; i<largestAttribute-strlen("Attributes"); i++) {printf(" ");}
	printf("|Data Types"); for (int i=0; i<largestDataType-strlen("Data Types"); i++) {printf(" ");}
	printf("|Keys"); for (int i=0; i<largestKey-strlen("Keys"); i++) {printf(" ");} printf("|\n");

	printf("+"); for (int i=0; i<largestAttribute; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestDataType; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestKey; i++) {printf("-");} printf("+\n");


	/* Printing Lower part of console-table (about all attributes & their properties). */

	while (!reachedEOF(fptr))
	{
		/* Attributes */

		charsPrinted = 0; printf("|"); c = fgetc(fptr);
		do {printf("%c", c); charsPrinted++; c = fgetc(fptr);} while (c!=' ' && c!=',');
		for (int i=0; i<largestAttribute-charsPrinted; i++) {printf(" ");}
		if (c==' ') {fseek(fptr, (ATTRIBUTE_MAX_LENGTH-1)-charsPrinted, SEEK_CUR);}
		

		/* Data Type */

		charsPrinted = 0; printf("|"); c = fgetc(fptr);
		do {printf("%c", c); charsPrinted++; c = fgetc(fptr);} while (c!=' ' && c!=',');
		for (int i=0; i<largestDataType-charsPrinted; i++) {printf(" ");}
		if (c==' ') {fseek(fptr, (DATA_TYPE_MAX_LENGTH-1)-charsPrinted, SEEK_CUR);}


		/* Key Type */

		charsPrinted = 0; printf("|"); c = fgetc(fptr);
		do {printf("%c", c); charsPrinted++; c = fgetc(fptr);} while (c!=' ' && c!=',');
		for (int i=0; i<largestKey-charsPrinted; i++) {printf(" ");}
		if (c==' ') {fseek(fptr, ((KEY_MAX_LENGTH-1)-charsPrinted)+2, SEEK_CUR);}
		else if (c==',') {fseek(fptr, 2, SEEK_CUR);} printf("|\n");


		/* Counting each encountered attribute for stats. */

		totalAttributes++;


		/* Safety mechanism to avoid reading garbage after EOF & then running in infinite loop. */

		c = fgetc(fptr);
		if (c!='\n') {break;}
		else if (c=='\n') {continue;}
	}

	printf("+"); for (int i=0; i<largestAttribute; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestDataType; i++) {printf("-");}
	printf("+"); for (int i=0; i<largestKey; i++) {printf("-");} printf("+\n");


	/* Showing total attributes encountered so far. */

	printf("STAT: Table contains %d attributes.\n\n", totalAttributes);


	/* Safely closing file descriptor. */

	fclose(fptr);
}










/* Shows all the available databases. */

void allDatabases()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int largestDb;
	int charsPrinted = 0, totalDb = 0;


	/* Opening metadata.tosbit with safety for NULL file descriptor. */

	fptr = fopen("data/metadata.tosbit", "r");
	if (fptr==NULL) {printf("ERROR: Data metadata not found!\n\n"); return;}


	/* Reading length of largest database name. */

	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestDb = atoi(metaBuff);
	fclose(fptr);
	

	/* Opening databases.tosbit with safety for NULL file descriptor. */

	fptr = fopen("data/databases.tosbit", "r");
	if (fptr==NULL) {printf("ERROR: Information for databases not found!\n\n"); return;}


	/* Printing header of the console-table (header of table). */

	printf("+"); for (int i=0; i<largestDb; i++) {printf("-");} printf("+\n");
	printf("|Databases"); for (int i=0; i<largestDb-strlen("Databases"); i++) {printf(" ");} printf("|\n");
	printf("+"); for (int i=0; i<largestDb; i++) {printf("-");} printf("+\n");


	/* Printing the lower part of the console-table (names of all databases). */

	while (!reachedEOF(fptr))
	{
		/* Printing a row on console for a database. */

		charsPrinted = 0; printf("|"); c = fgetc(fptr);
		do {printf("%c", c); charsPrinted++; c = fgetc(fptr);} while (c!=' ' && c!=',');
		for (int i=0; i<largestDb-charsPrinted; i++) {printf(" ");} printf("|\n");


		/* Counting each encountered database for stats. */

		totalDb++;


		/* Taking action depending on the position of FD cursor (space, \n or EOF). */

		if (c==' ')
		{
			fseek(fptr, ((DATABASE_MAX_LENGTH-1)-charsPrinted)-1, SEEK_CUR);


			/* Checking next byte & chossing action accordingly. */

			c = fgetc(fptr);
			if (c=='\n') {continue;}
			else if (reachedEOF(fptr)) {break;}
		}
		else if (c=='\n') {continue;}
		else if (reachedEOF(fptr)) {break;}
	}


	/* Printing tail of the console-table (the last line). */

	printf("+"); for (int i=0; i<largestDb; i++) {printf("-");} printf("+\n");


	/* Printing total number of databases as stats. */

	printf("STAT: %d databases found.\n\n", totalDb);


	/* Safely closing the file descriptor. */

	fclose(fptr);
}










/* Shows all available tables in the online database. */

void allTables()
{
	/* Initializations */

	char c;
	char metaBuff[2] = {0};
	int largestTable;
	int charsPrinted = 0, totalTable = 0;


	/*  from database.tosbit */

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/metadata.tosbit", database);


	/* Opening metadata.tosbit with safety for NULL file descriptor. */

	fptr = fopen(directory, "r");
	if (fptr==NULL) {printf("ERROR: Data metadata not found!\n\n"); return;}


	/* Reading length of largest table name. */

	for (int i=0; i<2; i++) {metaBuff[i] = fgetc(fptr);} largestTable = atoi(metaBuff);
	fclose(fptr);
	

	/* Opening tables.tosbit with safety for NULL file descriptor. */
	
	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/tables.tosbit", database);

	fptr = fopen(directory, "r");
	if (fptr==NULL) {printf("ERROR: Table information for \"%s\" not found!\n\n", database); return;}


	/* Printing header of the console-table (header of table). */

	printf("+"); for (int i=0; i<largestTable; i++) {printf("-");} printf("+\n");
	printf("|Tables"); for (int i=0; i<largestTable-strlen("Tables"); i++) {printf(" ");} printf("|\n");
	printf("+"); for (int i=0; i<largestTable; i++) {printf("-");} printf("+\n");


	/* Printing the lower part of the console-table (names of all databases). */

	while (!reachedEOF(fptr))
	{
		/* Printing a row on console for a database. */

		charsPrinted = 0; printf("|"); c = fgetc(fptr);
		do {printf("%c", c); charsPrinted++; c = fgetc(fptr);} while (c!=' ' && c!=',');
		for (int i=0; i<largestTable-charsPrinted; i++) {printf(" ");} printf("|\n");


		/* Counting each encountered database for stats. */

		totalTable++;


		/* Taking action depending on the position of FD cursor (space, \n or EOF). */

		if (c==' ')
		{
			fseek(fptr, ((TABLE_MAX_LENGTH-1)-charsPrinted)-1, SEEK_CUR);


			/* Checking next byte & chossing action accordingly. */

			c = fgetc(fptr);
			if (c=='\n') {continue;}
			else if (reachedEOF(fptr)) {break;}
		}
		else if (c=='\n') {continue;}
		else if (reachedEOF(fptr)) {break;}
	}


	/* Printing tail of the console-table (the last line). */

	printf("+"); for (int i=0; i<largestTable; i++) {printf("-");} printf("+\n");


	/* Printing total number of databases as stats. */

	printf("STAT: %d tables found.\n\n", totalTable);


	/* Safely closing the file descriptor. */

	fclose(fptr);
}










/* This funstion checks if a invalid data type was passed. (NOT "CASE INSENSITIVE") */

void checkDataType()
{
	/* Initializations */

	int state3 = 0, brk3 = 0, error = FALSE;



	/* Parsing data type syntax with Deterministic Finite Automata (DFA). */

	for (int i=0; i<strlen(dataType); i++)
	{
		switch (state3)
		{
			case 0: changeState(dataType[i], "iIsSfFbBmM", "1,1,4,4,10,10,16,16,20,20", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 1: changeState(dataType[i], "nN", "2,2", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 2: changeState(dataType[i], "tT", "3,3", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 3: changeState(dataType[i], " ", "3", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 4: changeState(dataType[i], "tT", "5,5", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 5: changeState(dataType[i], "rR", "6,6", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 6: changeState(dataType[i], "iI", "7,7", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 7: changeState(dataType[i], "nN", "8,8", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 8: changeState(dataType[i], "gG", "9,9", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 9: changeState(dataType[i], " ", "9", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 10: changeState(dataType[i], "lL", "11,11", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 11: changeState(dataType[i], "oO", "12,12", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 12: changeState(dataType[i], "aA", "13,13", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 13: changeState(dataType[i], "tT", "14,14", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 14: changeState(dataType[i], " ", "14", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 16: changeState(dataType[i], "oO", "17,17", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 17: changeState(dataType[i], "oO", "18,18", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 18: changeState(dataType[i], "lL", "19,19", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 19: changeState(dataType[i], " ", "19", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 20: changeState(dataType[i], "eE", "21,21", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 21: changeState(dataType[i], "dD", "22,22", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 22: changeState(dataType[i], "iI", "23,23", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 23: changeState(dataType[i], "aA", "24,24", &state3, 25); breakValue(&state3, 25, &brk3); break;
			case 24: changeState(dataType[i], " ", "24", &state3, 25); breakValue(&state3, 25, &brk3); break;
		}


		/* Breaking from loop early if DFA reaches dump state (error). */

		if (brk3==TRUE) {brk3 = FALSE; break;}
	}





	/* Taking decision or giving feedback as per DFA's stop state. */

	switch (state3)
	{
		case 0: printf("ERROR: (%s) Invalid data type passed!\n\n", dataType); break;
		case 1: printf("ERROR: Did you meant INT?\n\n"); break;
		case 2: printf("ERROR: Did you meant INT?\n\n"); break;
		case 4: printf("ERROR: Did you meant STRING?\n\n"); break;
		case 5: printf("ERROR: Did you meant STRING?\n\n"); break;
		case 6: printf("ERROR: Did you meant STRING?\n\n"); break;
		case 7: printf("ERROR: Did you meant STRING?\n\n"); break;
		case 8: printf("ERROR: Did you meant STRING?\n\n"); break;
		case 10: printf("ERROR: Did you meant FLOAT?\n\n"); break;
		case 11: printf("ERROR: Did you meant FLOAT?\n\n"); break;
		case 12: printf("ERROR: Did you meant FLOAT?\n\n"); break;
		case 13: printf("ERROR: Did you meant FLOAT?\n\n"); break;
		case 16: printf("ERROR: Did you meant BOOL?\n\n"); break;
		case 17: printf("ERROR: Did you meant BOOL?\n\n"); break;
		case 18: printf("ERROR: Did you meant BOOL?\n\n"); break;
		case 20: printf("ERROR: Did you meant MEDIA?\n\n"); break;
		case 21: printf("ERROR: Did you meant MEDIA?\n\n"); break;
		case 22: printf("ERROR: Did you meant MEDIA?\n\n"); break;
		case 23: printf("ERROR: Did you meant MEDIA?\n\n"); break;
		case 25: state2 = 8; error = TRUE; break;
	}
}










/* Creates a table & configures many files. */

void makeTable()
{
	char decision, c='$', c2='$';

	int write = TRUE, uniqueKey = FALSE;
	int charCount = 0, invCount = 0;

	char insertStr[64] = {0};



	if (checkDbExistence(FALSE)==FALSE)
	{
		printf("ERROR: No database opened yet!\n\n");
		write = FALSE;
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==TRUE))
	{
		printf("STAT: Table already exists!\n\n");
		printf("Overwrite data to disk? (y/n): "); decision = getchar();


		if (decision=='n') {write = FALSE;}

		else if (decision=='y')
		{
			clearEntity("directory");
			snprintf(directory, sizeof(directory), "cd data/%s && rm -rf %s", database, table);

			system(directory);
		}
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==FALSE))
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);
		fptr = fopen(directory, "r+");



		while (!(c2==']'&&c=='\n'))
		{
			charCount++;
			c2 = c; c = fgetc(fptr);

			if (c=='\"') {invCount++;}
		}

		fflush(fptr);


		if (invCount==2) {snprintf(insertStr, sizeof(insertStr), "\n\t\t\"%s\"\n\t]\n}", table);}
		else if (invCount>2) {snprintf(insertStr, sizeof(insertStr), ",\n\t\t\"%s\"\n\t]\n}", table);}


		fseek(fptr, (charCount-4), SEEK_SET);
		fputs(insertStr, fptr);
		fflush(fptr);



		fclose(fptr);
	}





	/* If new table is made, or if an exisiting table is overwritten. */

	if (write==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data/%s && mkdir %s", database, table);

		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);
		

		/* rows.json */

		fptr = fopen(directory, "w");
		fputs("{\n\t\"rows\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);



		/* details.json */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);

		fptr = fopen(directory, "w");


		fputs("{\n\t", fptr);
		fflush(fptr);


		for (int i=0; i<strlen(buffer); i++)
		{
			/* Purifying data type. */

			while (buffer[i]==' ') {i++;} clearEntity("dataType");
			while (buffer[i]!=' ') {dataType[strlen(dataType)] = buffer[i]; i++;}


			if (dataType[0]=='i' || dataType[0]=='I')
				{clearEntity("dataType"); strcpy(dataType,"int"); newline_remover(dataType);}

			else if (dataType[0]=='s' || dataType[0]=='S')
				{clearEntity("dataType"); strcpy(dataType,"string"); newline_remover(dataType);}

			else if (dataType[0]=='f' || dataType[0]=='F')
				{clearEntity("dataType"); strcpy(dataType,"float"); newline_remover(dataType);}

			else if (dataType[0]=='b' || dataType[0]=='B')
				{clearEntity("dataType"); strcpy(dataType,"bool"); newline_remover(dataType);}

			else if (dataType[0]=='m' || dataType[0]=='M')
				{clearEntity("dataType"); strcpy(dataType,"media"); newline_remover(dataType);}



			/* Traversing rest of the buffer for R/W ops. */

			while (buffer[i]==' ') {i++;} clearEntity("attribute");
			while (buffer[i]!=',' && i!=strlen(buffer)) {attribute[strlen(attribute)] = buffer[i]; i++;}



			/* Writing metadata to data/details.json with key constraints. */

			clearEntity("directory"); clearEntity("key");


			if ((dataType[0]=='m' || dataType[0]=='M') && !(attribute[0]=='$' || attribute[0]=='#')) {strcpy(key,"file");}
			else if ((dataType[0]=='m' || dataType[0]=='M') && (attribute[0]=='$' || attribute[0]=='#'))
			{
				snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);
				system(directory);
				printf("ERROR: Media attributes are hardwired to file keys!\n\n");

				return;
			}
			else if (attribute[0]=='$' && uniqueKey==FALSE) {strcpy(key,"unique"); uniqueKey = TRUE;}
			else if (attribute[0]=='$' && uniqueKey==TRUE)
			{
				snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);
				system(directory);
				printf("ERROR: A table can't have multiple unique keys!\n\n");

				return;
			}
			else if (attribute[0]=='#') {strcpy(key,"foreign");}
			else {strcpy(key,"regular");}


			newline_remover(key);

			snprintf(directory, sizeof(directory), "\"%s\": [\"%s\", \"%s\"]", attribute, dataType, key);
			fputs(directory, fptr);
			fflush(fptr);

			if (buffer[i]==',') {fputs(",\n\t", fptr);}
		}

		fputs("\n}", fptr);
		fflush(fptr);


		fclose(fptr);
		clearEntity("buffer");

		printf("OK: Table created successfully!\n\n");
	}
}










/* Make a database on user's request. */

void makeDb()
{
	char decision, c='$', c2='$';

	int write = TRUE;
	int charCount = 0, invCount = 0;

	char insertStr[64] = {0};


	
	/* If database already exists. */

	if (checkDbExistence(FALSE)==TRUE)
	{
		printf("STAT: Database already exists!\n\n");
		printf("Overwrite data to disk? (y/n): "); decision = getchar();


		if (decision=='n') {write=FALSE;}

		else if (decision=='y')
		{
			clearEntity("directory");
			snprintf(directory, sizeof(directory), "cd data && rm -rf %s", database);

			system(directory);
		}
	}



	/* If database doesn't exist. */

	else
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/databases.json");
		fptr = fopen(directory, "r+");



		while (!(c2==']'&&c=='\n'))
		{
			charCount++;
			c2 = c; c = fgetc(fptr);

			if (c=='\"') {invCount++;}
		}

		fflush(fptr);


		/* Insert into databases.json as per if any database exist or not. */

		if (invCount==2) {snprintf(insertStr, sizeof(insertStr), "\n\t\t\"%s\"\n\t]\n}", database);}
		else if (invCount>2) {snprintf(insertStr, sizeof(insertStr), ",\n\t\t\"%s\"\n\t]\n}", database);}

		fseek(fptr, (charCount-4), SEEK_SET);
		fputs(insertStr, fptr);
		fflush(fptr);



		fclose(fptr);
	}





	/* If new database is created, or if an existing one is overwritten. */

	if (write==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data && mkdir %s", database);

		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);



		/* tables.json */

		fopen(directory, "w");
		fputs("{\n\t\"tables\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);

		clearEntity("buffer");
		
		printf("OK: Database created successfully!\n\n");
	}
}










/* Deleting a table. */

void deleteTable()
{
	char c = '$', c2 = '$';
	int charCount = 0, invCount = 0;
	int head, tail;





	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n");}



	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
	}


	
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
	{
		/* Removing the table related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);

		system(directory);



		/* Erasing name from list of all available tables. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);

		fptr = fopen(directory, "r");



		while (invCount!=2)
		{
			c2 = c; c = fgetc(fptr); charCount++;
			if (c=='\"') {invCount++;}
		}





		/* Searching for two consecutive tab-spaces. */

		while (!reachedEOF(fptr))
		{	
			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c2=='\t' && c=='\t') {invCount++; head = charCount - 1;}

			} while (c!='\"');




			/* Storing characters to buffer. */

			clearEntity("buffer");

			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c!='\"') {buffer[strlen(buffer)] = c;}

			} while (c!='\"');



			if (!strcmp(table,buffer))
			{
				/* Searching for two consecutive tab-spaces. */

				while (!((c2=='\t' && c=='\t')||(c2=='\t' && c==']')))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					if ((c2=='\t' && c=='\t')||(c2=='\t' && c==']')) {invCount++; tail = charCount - 1;}
				}


				/* Pasting required content to 'chache.tosbit' file. */

				cache = fopen("data/cache.tosbit", "w");
				fseek(fptr, 0, SEEK_SET); charCount = 0;

				while (charCount!=head)
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);


				fseek(fptr, tail, SEEK_SET);


				/* WARNING: Beware! FEOF in any WHILE loop always reads an extra garbage value. */

				while (!reachedEOF(fptr))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fclose(fptr); fclose(cache);



				/* Write content in cache.tosbit to respective 'tables.json' */

				fptr = fopen(directory, "w");
				cache = fopen("data/cache.tosbit", "r");

				while (!reachedEOF(cache))
				{
					c2 = c; c = fgetc(cache); charCount++;

					fputc(c, fptr);
				}

				fflush(fptr);

				fclose(fptr); fclose(cache);

				system("rm -rf data/cache.tosbit");



				/* Removing ',' if last entry was read. ,\n\t]\n} */

				fptr = fopen(directory, "r+");
				fseek(fptr, -6, SEEK_END);

				if (fgetc(fptr)==',')
				{
					fseek(fptr, -1, SEEK_CUR);
					fputs("\n\t]\n} ", fptr);

					fflush(fptr);
				}

				fclose(fptr);



				printf("OK: Table deleted successfully!\n\n");
				break; // Why does this overwrites entire file if files not closed?
			}



			else if (strcmp(table,buffer)) {continue;}
		}
	}
}










/* Deleting a database. */

void deleteDb()
{
	char c = '$', c2 = '$';
	int charCount = 0, invCount = 0;
	int head, tail;





	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database named \"%s\" exists!\n\n", database);}



	else if (checkDbExistence(FALSE)==TRUE)
	{
		/* Removing the database related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s", database);

		system(directory);



		/* Erasing name from list of all available databases. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/databases.json");

		fptr = fopen(directory, "r");



		while (invCount!=2)
		{
			c2 = c; c = fgetc(fptr); charCount++;
			if (c=='\"') {invCount++;}
		}





		/* Searching for two consecutive tab-spaces. */

		while (!reachedEOF(fptr))
		{	
			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c2=='\t' && c=='\t') {invCount++; head = charCount - 1;}

			} while (c!='\"');




			/* Storing characters to buffer. */

			clearEntity("buffer");

			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c!='\"') {buffer[strlen(buffer)] = c;}

			} while (c!='\"');



			if (!strcmp(database,buffer))
			{
				/* Searching for two consecutive tab-spaces. */

				while (!((c2=='\t' && c=='\t')||(c2=='\t' && c==']')))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					if ((c2=='\t' && c=='\t')||(c2=='\t' && c==']')) {invCount++; tail = charCount - 1;}
				}


				/* Pasting required content to 'chache.tosbit' file. */

				cache = fopen("data/cache.tosbit", "w");
				fseek(fptr, 0, SEEK_SET); charCount = 0;

				while (charCount!=head)
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fseek(fptr, tail, SEEK_SET);


				/* WARNING: Beware! FEOF in any WHILE loop always reads an extra garbage value. */

				while (!reachedEOF(fptr))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fclose(fptr); fclose(cache);



				/* Write content in cache.tosbit to respective 'tables.json' */

				fptr = fopen(directory, "w");
				cache = fopen("data/cache.tosbit", "r");

				while (!reachedEOF(cache))
				{
					c2 = c; c = fgetc(cache); charCount++;

					fputc(c, fptr);
				}

				fflush(fptr);

				fclose(fptr); fclose(cache);

				system("rm -rf data/cache.tosbit");



				/* Removing ',' if last entry was read. ,\n\t]\n} */

				fptr = fopen(directory, "r+");
				fseek(fptr, -6, SEEK_END);

				if (fgetc(fptr)==',')
				{
					fseek(fptr, -1, SEEK_CUR);
					fputs("\n\t]\n} ", fptr);

					fflush(fptr);
				}

				fclose(fptr);



				printf("OK: Database deleted successfully!\n\n");
				break; // Why does this overwrites entire file if files not closed?
			}



			else if (strcmp(table,buffer)) {continue;}
		}
	}
}





/* Clears any requested table (clears of all data it holds). */

void clearTable()
{
	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n");}


	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
	}


	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
	{
		/* CLearing rows. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);

		fptr = fopen(directory, "w");

		fputs("{\n\t\"rows\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);


		/* Removing all zip files. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm data/%s/%s/*.xz", database, table);

		system(directory);


		printf("OK: Table cleared successfully!\n\n");
	}
}





/* Clear all the tables present in a database. */

void clearDb()
{
	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database named \"%s\" exists!\n\n", database);}


	else if (checkDbExistence(FALSE)==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s", database);
		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data && mkdir %s", database);
		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);


		/* tables.json */

		fopen(directory, "w");
		fputs("{\n\t\"tables\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);


		printf("OK: Database cleared successfully!\n\n");
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
		else {printf("ERROR: rows.json file for current table is corrupted!\n\n"); return TRUE;}

		// If having problem with "return", keep the "return TRUE;" line outside loop & break there.
	}
}










/* Data type parsing & validating automaton. */

int typeParser()
{
	int status;
	char c3 = '$';
	char pipedBuff[257] = {0}, shell_cmd[513] = {0};// size[9] = {0};

	FILE *media=NULL;



	/* int: Integers */

	if (!strcmp(dataType,"int"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 3); breakValue(&state2, 3, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "0123456789 ", "1,1,1,1,1,1,1,1,1,1,2", &state2, 3); breakValue(&state2, 3, &brk2); appendState(&state2, 1, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 4, &brk2); break;
				case 2: changeState(value[i], " ", "2", &state2, 3); breakValue(&state2, 3, &brk2); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as integer is blank!\n\n", pureValue); status = FALSE; break;
			case 1: state2 = 0; status = TRUE; break;
			case 2: state2 = 0; status = TRUE; break;
			case 3: printf("ERROR: (%s) An integer argument is expected!\n\n", pureValue); status = FALSE; break;
			case 4: printf("ERROR: (%s) Integer value passed exceeds 32 digits!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* string: String */

	else if (!strcmp(dataType,"string"))
	{
		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);

		if (strlen(pureValue)>VALUE_MAX_LENGTH-1) {printf("ERROR: (%s) String value passed exceeds 32 digits!\n\n", pureValue); status = FALSE;}
	}





	/* float: Floating point decimals */

	else if (!strcmp(dataType,"float"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); break; // Debug this headache, man...
				case 1: changeState(value[i], "0123456789.", "1,1,1,1,1,1,1,1,1,1,2", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); appendState(&state2, 2, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 2: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 3: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 4: changeState(value[i], " ", "4", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as float is blank!\n\n", pureValue); status = FALSE; break;
			case 1: printf("ERROR: (%s) Float has no decimal point!\n\n", pureValue); status = FALSE; break;
			case 2: printf("ERROR: (%s) No number written after decimal point!\n\n", pureValue); status = FALSE; break;
			case 3: state2 = 0; status = TRUE; break;
			case 4: state2 = 0; status = TRUE; break;
			case 5: printf("ERROR: (%s) Supposed float argument is not float!\n\n", pureValue); status = FALSE; break;
			case 6: printf("ERROR: (%s) Float value passed exceeds 32 digits!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* bool: Boolean */

	else if (!strcmp(dataType,"bool"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " ft", "0,1,6", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "a", "2", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 2, pureValue, value[i]); break;
				case 2: changeState(value[i], "l", "3", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 3, pureValue, value[i]); break;
				case 3: changeState(value[i], "s", "4", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 4, pureValue, value[i]); break;
				case 4: changeState(value[i], "e", "5", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 5, pureValue, value[i]); break;
				case 5: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
				case 6: changeState(value[i], "r", "7", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 7, pureValue, value[i]); break;
				case 7: changeState(value[i], "u", "8", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 8, pureValue, value[i]); break;
				case 8: changeState(value[i], "e", "9", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 9, pureValue, value[i]); break;
				case 9: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
				case 10: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as boolean is blank!\n\n", pureValue); status = FALSE; break;
			case 1: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 2: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 3: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 4: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 5: state2 = 0; status = TRUE; break;
			case 6: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 7: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 8: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 9: state2 = 0; status = TRUE; break;
			case 10: state2 = 0; status = TRUE; break;
			case 11: printf("ERROR: (%s) Argument is neither \"true\" or \"false\"!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* media: Media files (WARNING - To be put with file extension.) */

	else if (!strcmp(dataType,"media"))
	{
		/* Removing whitespaces. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);

		printf("Enter path for \"%s\": ", attribute);
		clearEntity("directory"); fgets(directory, sizeof(directory), stdin);
		newline_remover(directory);

		printf("\n");

		

		/*

		Checking existence of media file:

		media -> FD to check media file's existence.
		directory -> Path to media file.
		shell_cmd -> Complete shell command to copy target file.

		Path: /home/gouraarav/myCodes/trainers-crud-operation/client/index.html

		*/

		media = fopen(directory, "r");


		if (media==NULL) {printf("ERROR: (%s) No such file exists!\n\n", directory); status = FALSE;}
		
		else
		{
			fclose(media);
			printf("STAT: File is being compressed...\n");


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

			media = popen(shell_cmd, "r");
			do {c3 = fgetc(media); printf("%c", c3);} while (c3!='\t'); printf(" ->\t");

			pclose(media);


			memset(shell_cmd, 0, sizeof(shell_cmd));
			snprintf(shell_cmd, sizeof(shell_cmd), "du -h data/%s/%s/%s.xz", database, table, pureValue);

			media = popen(shell_cmd, "r");
			do {c3 = fgetc(media); printf("%c", c3);} while (c3!='\t'); printf("\n");
			
			pclose(media);



			status = TRUE;
		}
	}



	return status;
}










/* Pushing row into a table. {push to programmer(1, Gourav, 97.2)} */

void pushRow()
{
	/* Declarations */

	char c='$', c2='$';
	int commaCount=0, invCount=0, buffIndex=0, totalArg, currArg=0;
	char currAttribute[33]={0}, currDataType[33]={0}, currValue[33]={0};



	/* Queue objects (structures). */

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
		.showAll = Queue_showAll
	};

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
		.showAll = Queue_showAll
	};



	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);
	fptr = fopen(directory, "r");

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);
	fptr2 = fopen(directory, "r+");



	/* Safety checks */

	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n"); return;}
	else if (checkTableExistence(FALSE)==FALSE) {printf("ERROR: No table named \"%s\" exists!\n\n", table); return;}



	/* Checking number of argument (less or more or enough). */

	for (int i=0; i<strlen(buffer); i++) {if(buffer[i]==',') {commaCount++;}}
	totalArg = commaCount + 1;

	while (!reachedEOF(fptr))
	{
		c2 = c; c = fgetc(fptr);

		if (c=='\"') {invCount++;}
	}


	if ((totalArg)<(invCount/6)) {printf("ERROR: Very few values passed!\n\n"); fclose(fptr); fclose(fptr2); return;}
	else if ((totalArg)>(invCount/6)) {printf("ERROR: Too many arguments passed!\n\n"); fclose(fptr); fclose(fptr2); return;}

	invCount = 0;
	fseek(fptr, 0, SEEK_SET);



	/* Verifying data types of passed arguments. */

	while (!reachedEOF(fptr))
	{
		clearEntity("attribute"); clearEntity("dataType"); clearEntity("key"); clearEntity("value");

		currArg++;


		do {c2 = c; c = fgetc(fptr);} while (c!='\"');
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {attribute[strlen(attribute)] = c;}} while (c!='\"');

		fseek(fptr, 4, SEEK_CUR);	// Saving search computation time.
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {dataType[strlen(dataType)] = c;}} while (c!='\"');

		fseek(fptr, 3, SEEK_CUR);	// Saving search computation time.
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {key[strlen(key)] = c;}} while (c!='\"');

		for (int i=buffIndex; i<strlen(buffer); i++)
		{
			if (buffer[i]==',') {buffIndex = i + 1; break;}
			else {value[strlen(value)] = buffer[i];}
		}


		fseek(fptr, 3, SEEK_CUR);		// For checking if EOF reached afterwards.


		if (!strcmp(key,"unique"))		// ULTIMATE THING TO REPAIR/DEBUG
		{
			if (checkUnique(value, currArg, totalArg)==FALSE)
			{
				printf("ERROR: Duplicate for unique key \"%s\"!\n\n", attribute); return;
			}
		}


		if (typeParser()==FALSE) {return;}


		attributeQueue.queue(&attributeQueue, attribute);
		dataTypeQueue.queue(&dataTypeQueue, dataType);
		valueQueue.queue(&valueQueue, pureValue);
	}

	fclose(fptr);		// For "details.json"



	/* Inserting values. */

	fseek(fptr2, -6, SEEK_END);
	c2 = c; c = fgetc(fptr2);

	if (c=='}') {fputs(",\n", fptr2);}

	fputs("\n\t\t{", fptr2);


	for (int i=0; i<totalArg; i++)
	{
		/* Clearing strings & pasting the required value (for shorter string names). */

		memset(currAttribute, 0, sizeof(currAttribute));
		memset(currDataType, 0, sizeof(currDataType));
		memset(currValue, 0, sizeof(currValue));

		strcpy(currAttribute, attributeQueue.getValue(&attributeQueue,i));
		strcpy(currDataType, dataTypeQueue.getValue(&dataTypeQueue,i));
		strcpy(currValue, valueQueue.getValue(&valueQueue,i));



		/* Inserting arguments to JSON document. */

		clearEntity("buffer");
		snprintf(buffer, sizeof(buffer), "\n\t\t\t\"%s\": ", currAttribute);
		fputs(buffer, fptr2);

		clearEntity("buffer");

		if ((!strcmp(currDataType,"string"))||(!strcmp(currDataType,"media")))
		{
			snprintf(buffer, sizeof(buffer), "\"%s\"", currValue);
		}

		else
		{
			snprintf(buffer, sizeof(buffer), "%s", currValue);
		}

		fputs(buffer, fptr2);



		/* For non-last value, inserting comma. */

		if (i!=totalArg-1) {fputc(',', fptr2);}
	}



	/* Final insertions. */

	fputs("\n\t\t}\n\t]\n}", fptr2);



	/* Closing file descriptor & clear queues. */

	fclose(fptr2);
	
	attributeQueue.clear(&attributeQueue);
	dataTypeQueue.clear(&dataTypeQueue);
	valueQueue.clear(&dataTypeQueue);



	printf("OK: Row pushed successfully!\n\n");
}
