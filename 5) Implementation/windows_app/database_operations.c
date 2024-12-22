#ifndef DATABASE_OPERATIONS_C
	#define DATABASE_OPERATIONS_C

#include "database_operations.h"




















/* This function will print a coloured message & return back to white console colour. */

void colouredMessage(char *colour, char *str)
{
	if (!strcmp(colour,"red")) {red_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"green")) {green_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"blue")) {blue_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"yellow")) {yellow_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"cyan")) {cyan_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"pink")) {pink_console(); printf("%s", str); white_console();}
	else if (!strcmp(colour,"black")) {black_console(); printf("%s", str); white_console();}
}










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
	else if (!strcmp(str,"writer")) {memset(writer, 0, BUFFER_MAX_LENGTH*sizeof(char));}
}










/* Checks if the user requested database exists or not. */

int checkDbExistence(int msg)
{
	int existence = FALSE;

	snprintf(directory, sizeof(directory), "data\\%s\\tables.json", database);
	fptr = fopen(directory, "r");



	if (fptr==NULL && msg==TRUE)
	{
		red_console();
		printf("Error4: No database named \"%s\" exists!\n\n", database);
		white_console();

		clearEntity("database");
	}



	else
	{
		existence = TRUE;

		if (msg==TRUE)
		{
			green_console();
			printf("Database %s online!\n\n", database);
			white_console();
		}
	}



	fclose(fptr);

	return existence;
}










/* Checks if a user requested table exists or not. */

int checkTableExistence(int msg)
{
	int existence = FALSE;

	snprintf(directory, sizeof(directory), "data\\%s\\%s\\details.json", database, table);
	fptr = fopen(directory, "r");



	if (strlen(database)==0 && msg==TRUE) {colouredMessage("red", "No database opened yet!\n\n");}


	else if (fptr==NULL && msg==TRUE)
	{
		red_console();
		printf("No table named \"%s\" exists!\n\n", table);
		white_console();

		clearEntity("table");
	}


	else if (fptr!=NULL && msg==TRUE) {tableStructure(); existence = TRUE;}
	else if (fptr!=NULL && msg==FALSE) {existence = TRUE;}


	fclose(fptr);

	return existence;
}










/* Shows structure of the requested table (console design comes before fetching). */

void tableStructure()
{
	yellow_console();

	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n");
	printf("|         ATTRIBUTE NAME         | DATA TYPE | KEY TYPE |\n");
	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n");





	char c = '$', c2 = '$';

	while (!(c2==']' && c=='\n'))
	{

		// Printing the attribute name.

		printf("|");

		c = '$'; c2 = '$';


		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';

		printf("%s", buffer);
		for (int i=strlen(buffer); i<32; i++) {printf(" ");}





		// Printing the attribute data type.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';

		printf("%s", buffer);
		for (int i=strlen(buffer); i<11; i++) {printf(" ");}





		// Printing the key type of attribute.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}



		// Resetting is done at top to avoid detecting end of attribute in JSON file.



		printf("%s", buffer);
		for (int i=strlen(buffer); i<10; i++) {printf(" ");}
		printf("|\n");

		c = fgetc(fptr); c2 = c; c = fgetc(fptr);
	}





	c = '$'; c2 = '$';
	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n\n");

	clearEntity("buffer");
	fclose(fptr);

	white_console();
}











/* Shows all the available databases. */

void allDatabases()
{
	fptr = fopen("data\\databases.json", "r");
	if (fptr==NULL)
	{
		red_console();
		printf("\"databases.json\" file not found!\n\n", database);
		white_console();
	}

	char c = '$';
	int count = 0, reading = FALSE;



	while (count!=3)
	{
		c = fgetc(fptr);

		if (c=='\"') {count++;}

		if (feof(fptr)) {colouredMessage("yellow", "No databases found!\n\n");}
	}



	reading = TRUE;
	clearEntity("buffer");
	c = fgetc(fptr);						// Advance reading byte after ("), to enter while loop. 



	yellow_console();

	printf("+----------------+\n");
	printf("|   DATABASES    |\n");
	printf("+----------------+\n");

	while (!feof(fptr))
	{
		while (c!='\"') {buffer[strlen(buffer)] = c; c = fgetc(fptr);}

		reading = FALSE;
		c = '$';

		printf("|%s", buffer);
		for (int i=strlen(buffer); i<16; i++) {printf(" ");}
		printf("|\n");

		clearEntity("buffer");



		while (c!='\"')
		{
			c = fgetc(fptr);
			if (feof(fptr)) {break;}
		}

		reading = TRUE;

		c = fgetc(fptr);			// Advance reading byte after ("), to enter while loop. 
	}



	clearEntity("buffer");
	fclose(fptr);



	printf("+----------------+\n\n");
	white_console();
}










/* Shows all available tables in the online database. */

void allTables()
{
	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data\\%s\\tables.json", database);

	fptr = fopen(directory, "r");
	if (fptr==NULL)
	{
		red_console();
		printf("No database named \"%s\" exists.\n\n", database);
		white_console();

		return;
	}

	char c = '$';
	int count = 0, reading = FALSE;



	while (count!=3)
	{
		c = fgetc(fptr);

		if (c=='\"') {count++;}

		if (feof(fptr)) {colouredMessage("yellow", "No tables found!\n\n");}
	}



	reading = TRUE;
	clearEntity("buffer");
	c = fgetc(fptr);						// Advance reading byte after ("), to enter while loop. 



	yellow_console();

	printf("+----------------+\n");
	printf("|    TABLES      |\n");
	printf("+----------------+\n");

	while (!feof(fptr))
	{
		while (c!='\"') {buffer[strlen(buffer)] = c; c = fgetc(fptr);}

		reading = FALSE;
		c = '$';

		printf("|%s", buffer);
		for (int i=strlen(buffer); i<16; i++) {printf(" ");}
		printf("|\n");

		clearEntity("buffer");



		while (c!='\"')
		{
			c = fgetc(fptr);
			if (feof(fptr)) {break;}
		}

		reading = TRUE;

		c = fgetc(fptr);			// Advance reading byte after ("), to enter while loop. 
	}



	clearEntity("buffer");
	fclose(fptr);



	printf("+----------------+\n\n");
	white_console();
}










/* This funstion checks if a invalid data type was passed. (MAKE THEM CASE INSENSITIVE) */

void checkDataType()
{
	if ((!strcmp(dataType,"int"))||(!strcmp(dataType,"float"))||(!strcmp(dataType,"string"))||(!strcmp(dataType,"bool"))) {}
	else {valid = FALSE; state2 = 8; brk2 = TRUE;}
}










/* Creates a table & configures many files. */

void makeTable()
{
	char decision, c='$', c2='$';

	int write = TRUE;
	int charCount = 0;

	char *fileBuffer;



	if (checkDbExistence(FALSE)==FALSE)
	{
		colouredMessage("red", "No database opened yet!\n\n");
		write = FALSE;
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==TRUE))
	{
		colouredMessage("red", "Table already exists!\n\n");
		colouredMessage("yellow", "Overwrite data to disk? (y/n): "); decision = getchar();


		if (decision=='n') {write = FALSE;}

		else if (decision=='y')
		{
			clearEntity("directory");
			snprintf(directory, sizeof(directory), "cd data\\%s && rmdir /S /Q %s", database, table);

			system(directory);
		}
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==FALSE))
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data\\%s\\tables.json", database);
		fptr = fopen(directory, "r");



		/* Dynamic memory allocation for R/W operations on file (safety mechanism). */

		fileBuffer = malloc(TABLES_JSON_DEFAULT*sizeof(char));


		while (c2=='\"' && c=='\n')
		{
			c2 = c; c = fgetc(fptr);

			if (c==',') {realloc(fileBuffer, EXPANSION_SIZE*sizeof(char));}

			fileBuffer[strlen(fileBuffer)] = c;
		}


		realloc(fileBuffer, EXPANSION_SIZE*sizeof(char));
		// CONTINUE FROM HERE...


		free(fileBuffer);
		fclose(fptr);
	}





	/* If new table is made, or if an exisiting table is overwritten. */

	if (write==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data\\%s && mkdir %s", database, table);

		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data\\%s\\%s\\rows.json", database, table);

		fptr = fopen(directory, "w");
		fputs("{\n\t\"rows\": [\n\t]\n}", fptr);
		fflush(fptr);								// Forcefully write to file

		fclose(fptr);



		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data\\%s\\%s\\details.json", database, table);

		fptr = fopen(directory, "w");
		fclose(fptr);

		colouredMessage("green", "Table created successfully!\n\n");
	}
}




















#endif