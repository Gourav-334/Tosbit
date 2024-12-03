/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_C
	#define SYNTAX_PARSER_C



#include "syntax_parser.h"










/*

STATISTICS:

Total DFA states: 				15

Total error types: 				7
Total acknowledgement types:	2

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
	/* Will save each line of script in each node */

	struct Queue script = {.n=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};





	while (TRUE)
	{
		printf("TOS> ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);
		memset((command + strlen(command)), 0, (COMMAND_MAX_LENGTH-strlen(command))*sizeof(char));



		if (illegalChars(command, "\"[]")==TRUE)
		{
			red_console();
			printf("Error9: Please don't use \", [ or ]\n\n");
			white_console();

			continue;
		}





		/* Automaton starts running & moves until whole syntax has been read */

		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0:

					if (command[i]==' ' || command[i]=='\0' || strlen(command)==1) {}
					else if (command[i]=='@') {state = 1;}
					else if (command[i]=='o' || command[i]=='O') {state = 3;}
					else if (command[i]=='s') {state = 16;}
					else {state = 2;}

					break;



				case 1:

					if (command[i]=='@') {state = 0;}
					else {}

					break;



				case 2:

					brk = TRUE;

					break;



				case 3:

					if (command[i]=='p' || command[i]=='P') {state = 4;}
					else {state = 2;}

					break;



				case 4:

					if (command[i]=='e' || command[i]=='E') {state = 5;}
					else {state = 11; brk = TRUE;}

					break;



				case 5:

					if (command[i]=='n' || command[i]=='N') {state = 6;}
					else {state = 11; brk = TRUE;}

					break;



				case 6:

					if (command[i]==' ') {state = 13;}
					else {state = 11; brk = TRUE;}

					break;



				case 7:

					if (command[i]=='b'  || command[i]=='B') {state = 8;}
					else {state = 11; brk = TRUE;}

					break;



				case 8:

					if (command[i]==' ') {state = 14;}
					else {state = 11; brk = TRUE;}

					break;



				case 9:

					if (command[i]==' ') {state = 10;}
					
					else
					{
						if (strlen(database)==32) {state = 15; brk = TRUE;}
						else {database[strlen(database)] = command[i];}
					}

					break;



				case 10:

					if (command[i]==' ') {}
					else {state = 12; brk = TRUE;}

					break;



				case 13:

					if (command[i]==' ') {}
					else if (command[i]=='d' || command[i]=='D') {state = 7;}
					else {state = 11; brk = TRUE;}

					break;



				case 14:

					memset(database, 0, DATABASE_MAX_LENGTH*sizeof(char));

					if (command[i]==' ') {}
					
					else
					{
						state = 9;
						database[strlen(database)] = command[i];
					}

					break;



				case 16:

					if (command[i]=='h' || command[i]=='H') {state = 17;}
					else {state = 28; brk = TRUE;}

					break;



				case 17:

					if (command[i]=='o' || command[i]=='O') {state = 18;}
					else {state = 28; brk = TRUE;}

					break;



				case 18:

					if (command[i]=='w'  || command[i]=='W') {state = 19;}
					else {state = 28; brk = TRUE;}

					break;



				case 19:

					if (command[i]==' ') {state = 20;}
					else {state = 28; brk = TRUE;}

					break;



				case 20:

					if (command[i]==' ') {}
					else if (command[i]=='s' || command[i]=='S') {state = 22;}
					else {state = 28;}

					break;



				case 21:

					if (command[i]==' ') {state = 29;}
					else {table[strlen(table)] = command[i];}

					break;



				case 22:

					if (command[i]=='t' || command[i]=='T') {state = 23;}
					else {state = 28; brk = TRUE;}

					break;



				case 23:

					if (command[i]=='r' || command[i]=='R') {state = 24;}
					else {state = 28; brk = TRUE;}

					break;



				case 24:

					if (command[i]=='u' || command[i]=='U') {state = 25;}
					else {state = 28; brk = TRUE;}

					break;



				case 25:

					if (command[i]=='c' || command[i]=='C') {state = 26;}
					else {state = 28; brk = TRUE;}

					break;



				case 26:

					if (command[i]=='t' || command[i]=='T') {state = 27;}
					else {state = 28; brk = TRUE;}

					break;



				case 27:

					memset(table, 0, TABLE_MAX_LENGTH*sizeof(char));

					if (command[i]==' ') {state = 30;}
					else {state = 28; brk = TRUE;}

					break;



				case 29:

					if (command[i]==' ') {}
					else {state = 28;}

					break;



				case 30:

					if (command[i]==' ') {}

					else
					{
						table[strlen(table)] = command[i];
						state = 21;
					}

					break;



			

				break;		// What is its purpose? Is it necessary?
			}



			if (brk==TRUE) {brk = FALSE; break;}
			if (i==strlen(command)-2) {break;}
		}










		/* Final state, NOT accept state. Its the result after whole syntax has been read */

		switch (state)
		{
			case 0:

				green_console();
				Queue_queue(&script, command);
				printf("No changes are made!\n\n");
				white_console();

				break;



			case 1:

				red_console();
				printf("Error1: Comment brackets opened, but not closed!\n\n");
				white_console();

				break;



			case 2:

				red_console();
				printf("Error2: Unknown command passed!\n\n");
				white_console();

				break;



			case 3:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 4:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 5:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 6:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 7:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 8:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 9:

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


				break;



			case 10:

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

				break;



			case 11:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 12:

				red_console();
				printf("Error7: Did you meant open db %s?\n\n", database);
				white_console();

				break;



			case 13:

				red_console();
				printf("Error3: Did you meant \"open db db_name\"?\n\n");
				white_console();

				break;



			case 14:

				red_console();
				printf("Error5: No database name entered!\n\n");
				white_console();

				break;



			case 15:

				red_console();
				printf("Error6: Name of database must be 32 characters long at max!\n\n");
				white_console();

				break;



			case 16:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 17:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 18:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 19:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 20:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 21:

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
					yellow_console();
					printf("Table %s online!\n\n", table);
					white_console();
				}

				break;



			case 22:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 23:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 24:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 25:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 26:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 27:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 28:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;



			case 29:

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
					yellow_console();
					printf("Table %s online!\n\n", table);
					white_console();
				}

				break;



			case 30:

				red_console();
				printf("Error8: Did you meant \"show struct table_name\"?\n\n");
				white_console();

				break;
		}





		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));

		state = 0;
	}





	Queue_clear(&script);
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */