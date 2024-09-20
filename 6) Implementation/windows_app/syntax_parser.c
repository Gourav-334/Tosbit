/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_C
	#define SYNTAX_PARSER_C



#include "syntax_parser.h"










/*

STATISTICS:

Total DFA states: 				14
Total error types: 				2
Total acknowledgement types:	1
Total unexpected bugs:			1
Total silly bugs:				1

*/










/*

TO DEBUG:

i) For some reason, an extra character is getting read, leaving a blank or '\n'.
ii) The state remains the last one for some reason.
iii) Even if user passes a blank command, the stdin takes an invisible character.



SOLUTION:

i) We terminate the loop after reading the 2nd last character of entered string (excluding the
unexpected character).
ii) Change the state to 0 after line analysis is complete, bloody fool!
iii) Bandage the program by assuming having read a character (continue from 2nd character).

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





		/* Automaton starts running & moves until whole syntax has been read */

		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0:

					if (command[i]==' ' || command[i]=='\0' || strlen(command)==1) {}
					else if (command[i]=='@') {state = 1;}
					else if (command[i]=='o') {state = 3;}
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

					if (command[i]=='p') {state = 4;}
					else {state = 2;}

					break;



				case 4:

					if (command[i]=='e') {state = 5;}
					else {state = 11; brk = TRUE;}

					break;



				case 5:

					if (command[i]=='n') {state = 6;}
					else {state = 11; brk = TRUE;}

					break;



				case 6:

					if (command[i]==' ') {state = 13;}
					else {state = 11; brk = TRUE;}

					break;



				case 7:

					if (command[i]=='b') {state = 8;}
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
					else if (command[i]=='d') {state = 7;}
					else {state = 11; brk = TRUE;}

					break;



				case 14:

					if (command[i]==' ') {}
					
					else
					{
						state = 9;
						database[strlen(database)] = command[i];
					}

				break;
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

				sprintf(directory, "data\\database\\%s.tos", encrypt(database));
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
					printf("Database %s online.\n\n", database);
					white_console();
				}

				break;



			case 10:

				sprintf(directory, "data\\database\\%s.tos", encrypt(database));
				fptr = fopen(directory, "r");

				if (fptr==NULL)
				{
					red_console();
					printf("Error4: No database named %s exists!\n\n", database);
					white_console();
				}

				else
				{
					green_console();
					printf("Database %s online.\n\n", database);
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
		}





		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));
		state = 0;
	}





	Queue_clear(&script);
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */