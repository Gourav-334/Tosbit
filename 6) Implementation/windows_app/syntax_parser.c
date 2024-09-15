/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SYNTAX_PARSER_C
	#define SYNTAX_PARSER_C



#include "syntax_parser.h"










/*

TO DEBUG:

i) "Case 2" is executing for no reason, but also print "\n" before executing. How the fuck is it
reaching state 2!?

*/










/* Tokenizes strings into pieces as per depending characters, like space */

void syntax_processing()
{
	while (TRUE)
	{
		printf("TOS> ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);



		for (int i=0; i<COMMAND_MAX_LENGTH; i++)
		{
			switch (state)
			{
				case 0: printf("%d, %c\n", state, command[i]); ////////////////////////////
					if (command[i]==' ') {}
					else if (command[i]=='@') {state = 1;}
					else {state = 2;}

					break;

				case 1: printf("%d, %c\n", state, command[i]); ////////////////////////////
					if (command[i]=='@') {state = 0;}
					else {}

					break;

				case 2: printf("%d, %c\n", state, command[i]); ////////////////////////////
					brk = 1;

					break;
			}



			if (brk==1) {brk = 0; break;}
		}



		switch (state)
		{
			case 0: ack1(); break;
			case 1: error1(); break;
			case 2: error2(); break;
		}



		memset(command, 0, COMMAND_MAX_LENGTH);
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