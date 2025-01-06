#ifndef TRANSITION_TOOL_TESTER_C
	#define TRANSITION_TOOL_TESTER_C

#include "transition_tool.h"










/* Change one state to another as per the given state & input symbol.
PRECAUTION: Don't include string terminator in symbol[] or transition[]. */

void changeState(char input, char symbols[], char transition[], int *state, int dump)
{
	int index, commas=0, flag=FALSE;
	char str[4] = {0};



	for (int i=0; i<strlen(symbols); i++) // REAL PROBLEM...
	{
		printf("input: %c\tsymbols[i]: %c\tindex: %d\tflag: %d\n",
			input, symbols[i], index, flag);

		if (input==symbols[i]) {index = i; flag = TRUE; break;}
	}



	if (flag==FALSE) {*state = dump;}

	else if (flag==TRUE)
	{
		for (int i=0; i<strlen(transition); i++)
		{
			printf("transition[i]: %c\tcommas: %d\tindex: %d\tstr: %s\tatoi(str): %d\t",
				transition[i], commas, index, str, atoi(str));

			if (transition[i]==',' && commas<index) {printf("@\n"); commas++;}
			else if (transition[i]!=',' && commas==index) {printf("#\n"); str[strlen(str)] = transition[i];}
			else if (transition[i]==',' && commas==index) {printf("$\n"); break;}
			else {printf("&\n"); continue;}
		}

		*state = atoi(str);
	}


	
	printf("\nSTATE: %d\n\n", *state);
}










#endif