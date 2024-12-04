#ifndef TRANSITION_TOOL_C
	#define TRANSITION_TOOL_C

#include "transition_tool.h"










/* Change one state to another as per the given state & input symbol.
PRECAUTION: Don't include string terminator in symbol[] or transition[]. */

void changeState(char input, char symbols[], char transition[], int *state, int dump)
{
	int index, commas=0, flag=FALSE;
	char str[4] = {0};



	for (int i=0; i<strlen(symbols); i++)
	{
		if (input==symbols[i]) {index = i; flag = TRUE; break;}
	}



	if (flag==FALSE) {*state = dump;}

	else if (flag==TRUE)
	{
		for (int i=0; i<strlen(transition); i++)
		{
			if (transition[i]==',' && commas<index) {commas++;}
			else if (transition[i]!=',' && commas==index) {str[strlen(str)] = transition[i];}
			else if (transition[i]==',' && commas==index) {break;}
			else {continue;}
		}

		*state = atoi(str);
	}
}










/* Sets up the break condition as per a given state. */

void breakValue(int *state, int breakState, int *brk)
{
	if (*state==breakState) {*brk = TRUE;}
}










/* Appends a character to a given string. */

void appendState(int *state, int breakState, char *target, char value)
{
	if (*state==breakState)
	{
		target[strlen(target)] = value;
	}
}










#endif