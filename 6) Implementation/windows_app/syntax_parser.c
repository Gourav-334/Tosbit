/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_C
	#define SYNTAX_PARSER_C



#include "syntax_parser.h"










/*

TO DEBUG:

i) For some reason, an extra character is getting read, leaving a blank or '\n'.
ii) The state remains the last one for some reasons.



SOLUTION:

i) We terminate the loop after reading the 2nd last character of entered string (excluding the
unexpected character).
ii) Change the state to 0 after line analysis is complete, fool.

*/










/* Tokenizes strings into pieces as per depending characters, like space */

void syntax_processing(char username[])
{
	while (TRUE)
	{
		printf("TOS> ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);
		memset((command + strlen(command)), 0, (COMMAND_MAX_LENGTH-strlen(command))*sizeof(char));



		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0:

					if (command[i]==' ' || command[i]=='\0') {}
					else if (command[i]=='@') {state = 1;}
					else {state = 2;}

					break;



				case 1:

					if (command[i]=='@') {state = 0;}
					else {}

					break;



				case 2:

					brk = 1;

					break;
			}



			if (brk==1) {brk = 0; break;}
			if (i==strlen(command)-2) {break;}
		}



		switch (state)
		{
			case 0: ack1(); break;
			case 1: error1(); break;
			case 2: error2(); break;
		}



		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));
		state = 0;
	}
}





/* Acknowledges that no changes are made */

void ack1()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	printf("No changes are made!\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}





/* Error for leaving comment open */

void error1()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	printf("Error1: Comment brackets opened, but not closed!\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}





/* Tells if an unknown command is passed */

void error2()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	printf("Error2: Unknown command passed!\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */