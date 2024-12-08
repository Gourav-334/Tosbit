/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_C
	#define SYNTAX_PARSER_C



#include "syntax_parser.h"










/*

STATISTICS:

Total DFA states: 				30

Total error types: 				10
Total acknowledgement types:	4

Total strange bugs:				5
Total silly bugs:				3

*/










/*

TO DEBUG:

i) For some reason, an extra character is getting read, leaving a blank or '\n'.
ii) The state remains the last one for some reason.
iii) Even if user passes a blank command, the stdin takes an invisible character.
iv) If a database is found to exist, the same database can't be found the next time.
v) memset() functions are getting skipped for unknown reason.
vi) Not only string formatting functions but my own strappend() is recursively adding the varaible
(if mentioned), not the directly passed strings. It has to do something with strappend() only, encrypter
is derived from it.
vii) Case 9, buffer has first character as space after emptying or maybe doesn't empty properly.



SOLUTION:

i) We terminate the loop after reading the 2nd last character of entered string (excluding the
unexpected character).
ii) Change the state to 0 after line analysis is complete, bloody fool!
iii) Bandage the program by assuming having read a character (continue from 2nd character).
iv) Check the formatted string function & state transitions.
v) It isn't skipped! You are trying to print the string after emptying it, idiot!
vi) Something is wrong with either variable "database" or the functions, or even variable "directory".
vii) First check if it is being emptied properly or not & then bandage it if required.

*/














/* The automaton, each state has to be defined for all situations. */

void syntax_parser(char username[])
{
	struct Queue script = {.n=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};



	while (TRUE)
	{
		printf("TOS> ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);
		memset((command + strlen(command)), 0, (COMMAND_MAX_LENGTH-strlen(command))*sizeof(char));



		if (illegalChars(command, "\"[]")==TRUE)
			{colouredMessage("red", "Error9: Please don't use \", [ or ]\n\n"); continue;}





		/* Automaton starts running & moves until whole syntax has been read */

		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0: changeState(command[i], " @oOsS", "0,1,3,3,16,16", &state, 2); break;
				case 1: changeState(command[i], "@", "0", &state, 1); break;
				case 2: brk = TRUE; break;
				case 3: changeState(command[i], "pP", "4,4", &state, 2); break;
				case 4: changeState(command[i], "eE", "5,5", &state, 11); breakValue(&state, 11, &brk); break;
				case 5: changeState(command[i], "nN", "6,6", &state, 11); breakValue(&state, 11, &brk); break;
				case 6: changeState(command[i], " ", "13", &state, 11); breakValue(&state, 11, &brk); break;
				case 7: changeState(command[i], "bB", "8,8", &state, 11); breakValue(&state, 11, &brk); break;
				case 8: changeState(command[i], " ", "14", &state, 11); breakValue(&state, 11, &brk); break;
				case 9: changeState(command[i], " ", "10", &state, 9); appendState(&state, 9, database, command[i]); limitChecker(database, 32, &state, 15, &brk); break;
				case 10: changeState(command[i], " ", "10", &state, 12); breakValue(&state, 12, &brk); break;
				case 13: changeState(command[i], " dD", "13,7,7", &state, 11); breakValue(&state, 11, &brk); break;
				case 14: clearEntity("database"); changeState(command[i], " ", "14", &state, 9); appendState(&state, 9, database, command[i]); break;
				case 16: changeState(command[i], "hH", "17,17", &state, 28); breakValue(&state, 28, &brk); break;
				case 17: changeState(command[i], "oO", "18,18", &state, 28); breakValue(&state, 28, &brk); break;
				case 18: changeState(command[i], "wW", "19,19", &state, 28); breakValue(&state, 28, &brk); break;
				case 19: changeState(command[i], " ", "20", &state, 28); breakValue(&state, 28, &brk); break;
				case 20: changeState(command[i], " sS", "20,22,22", &state, 28); break;
				case 21: changeState(command[i], " ", "29", &state, 21); appendState(&state, 21, table, command[i]); break;
				case 22: changeState(command[i], "tT", "23,23", &state, 28); breakValue(&state, 28, &brk); break;
				case 23: changeState(command[i], "rR", "24,24", &state, 28); breakValue(&state, 28, &brk); break;
				case 24: changeState(command[i], "uU", "25,25", &state, 28); breakValue(&state, 28, &brk); break;
				case 25: changeState(command[i], "cC", "26,26", &state, 28); breakValue(&state, 28, &brk); break;
				case 26: changeState(command[i], "tT", "27,27", &state, 28); breakValue(&state, 28, &brk); break;
				case 27: clearEntity("table"); changeState(command[i], " ", "30", &state, 28); breakValue(&state, 28, &brk); break;
				case 29: changeState(command[i], " ", "29", &state, 28); break;
				case 30: changeState(command[i], " ", "30", &state, 21); appendState(&state, 21, table, command[i]); break;
			}


			if (brk==TRUE) {brk = FALSE; break;}
			if (i==strlen(command)-2) {break;}
		}










		/* Final state, NOT accept state. Its the result after whole syntax has been read */

		switch (state)
		{
			case 0: Queue_queue(&script, command); colouredMessage("green", "No changes are made!\n\n"); break;
			case 1: colouredMessage("red", "Error1: Comment brackets opened, but not closed!\n\n"); break;
			case 2: colouredMessage("red", "Error2: Unknown command passed!\n\n"); break;
			case 3: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 4: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 5: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 6: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 7: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 8: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 9: checkDbExistence(fptr); break;
			case 10: checkDbExistence(fptr); break;
			case 11: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 12: colouredMessage("red", "Error7: Did you meant open db %s?\n\n"); break;
			case 13: colouredMessage("red", "Error3: Did you meant \"open db db_name\"?\n\n"); break;
			case 14: colouredMessage("red", "Error5: No database name entered!\n\n"); break;
			case 15: colouredMessage("red", "Error6: Name of database must be 32 characters long at max!\n\n"); break;
			case 16: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 17: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 18: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 19: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 20: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 21: checkTableExistence(fptr); break;
			case 22: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 23: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 24: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 25: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 26: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 27: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 28: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
			case 29: checkTableExistence(fptr); break;
			case 30: colouredMessage("red", "Error8: Did you meant \"show struct table_name\"?\n\n"); break;
		}



		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));

		state = 0;
	}





	Queue_clear(&script);
}




















// Internal functions


/* This function clears a string, identified through entered value of string. */

void clearEntity(char *str)
{
	if (!strcmp(str,"command")) {memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"database")) {memset(database, 0, DATABASE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"table")) {memset(table, 0, TABLE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"directory")) {memset(directory, 0, DIRECTORY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"buffer")) {memset(buffer, 0, BUFFER_MAX_LENGTH*sizeof(char));}
}










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










/* Checks if the user requested database exists or not. */

void checkDbExistence(FILE *fptr)
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

void checkTableExistence(FILE *fptr)
{
	snprintf(directory, sizeof(directory), "data\\%s\\%s\\details.json", database, table);
	fptr = fopen(directory, "r");



	if (fptr==NULL)
	{
		red_console();
		printf("Error10: No table named \"%s\" exists!\n\n", table);
		white_console();
	}


	else
	{
		tableStructure(fptr);
	}
}










/* Shows structure of the requested table (console design comes before fetching). */

void tableStructure(FILE *fptr)
{
	yellow_console();

	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n");
	printf("|         ATTRIBUTE NAME         | DATA TYPE | KEY TYPE |\n");
	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n");

	while (c2!=']' && c!='\n')
	{
		// Printing the attribute name.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			clearEntity("buffer"); buffer[strlen(buffer)] = c;
		}

		printf("%s", buffer);
		for (int i=strlen(buffer); i<32; i++) {printf(" ");}



		// Printing the attribute data type.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			clearEntity("buffer"); buffer[strlen(buffer)] = c;
		}

		printf("%s", buffer);
		for (int i=strlen(buffer); i<11; i++) {printf(" ");}



		// Printing the key type of attribute.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			clearEntity("buffer"); buffer[strlen(buffer)] = c;
		}

		printf("%s", buffer);
		for (int i=strlen(buffer); i<10; i++) {printf(" ");}
		printf("|\n");
	}

	for (int i=0; i<(32+11+10+4); i++) {printf("-");} printf("\n\n");

	white_console();
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */