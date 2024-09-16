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



SOLUTION:

i) We terminate the loop after reading the 2nd last character of entered string (excluding the
unexpected character).
ii) Change the state to 0 after line analysis is complete, bloody fool!

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

					if (command[i]==' ' || command[i]=='\0') {}
					else if (command[i]=='@') {state = 1;}
					else if (command[i]=='o') {state = 3;}
					else {state = 2;}

					break;



				case 1:

					if (command[i]=='@') {state = 0;}
					else {}

					break;



				case 2:

					brk = 1;

					break;



				case 3:

					if (command[i]=='p') {state = 4;}
					else {state = 2;}

					break;



				case 4:

					if (command[i]=='e') {state = 5;}
					else {state = 2;}

					break;



				case 5:

					if (command[i]=='n') {state = 6;}
					else {state = 2;}

					break;



				case 6:	// THIS IS WHERE YOU LEFT!

					if (command[i]==' ') {}
					//else if (command[i]==)
					else {state = 2;}

					break;
			}



			if (brk==1) {brk = 0; break;}
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
		}





		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));
		state = 0;
	}





	Queue_clear(&script);
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */