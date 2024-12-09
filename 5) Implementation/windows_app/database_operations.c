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
}










/* Checks if the user requested database exists or not. */

void checkDbExistence()
{
	snprintf(directory, sizeof(directory), "data\\%s\\tables.json", database);
	fptr = fopen(directory, "r");



	if (fptr==NULL)
	{
		red_console();
		printf("Error4: No database named \"%s\" exists!\n\n", database);
		white_console();
	}


	else
	{
		green_console();
		printf("Database %s online!\n\n", database);
		white_console();
	}
}










/* Checks if a user requested table exists or not. */

void checkTableExistence()
{
	snprintf(directory, sizeof(directory), "data\\%s\\%s\\details.json", database, table);
	fptr = fopen(directory, "r");



	if (fptr==NULL)
	{
		red_console();
		printf("Error10: No table named \"%s\" exists!\n\n", table);
		white_console();
	}


	else {tableStructure(fptr, buffer);}
}










/* Shows structure of the requested table (console design comes before fetching). */

void tableStructure()
{
	yellow_console();

	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n");
	printf("|         ATTRIBUTE NAME         | DATA TYPE | KEY TYPE |\n");
	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n");



	char c = '$', c2 = '$';

	while (!(c2==']' && c=='\n'))
	{
		// Printing the attribute name.

		printf("|");

		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "


		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "

		memset(buffer, 0, sizeof(char)*strlen(buffer)); // SOMETHING MIGHT HAPPEN..................

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "

		printf("%s", buffer);
		for (int i=strlen(buffer); i<32; i++) {printf(" ");}



		// Printing the attribute data type.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "

		memset(buffer, 0, sizeof(char)*strlen(buffer)); // SOMETHING MIGHT HAPPEN..................

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "

		printf("%s", buffer);
		for (int i=strlen(buffer); i<11; i++) {printf(" ");}



		// Printing the key type of attribute.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';		// Reset c & c2's values to read upcoming "

		memset(buffer, 0, sizeof(char)*strlen(buffer)); // SOMETHING MIGHT HAPPEN..................

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
	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n\n");

	white_console();
}




















#endif