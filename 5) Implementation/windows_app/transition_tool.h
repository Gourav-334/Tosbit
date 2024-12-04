#ifndef TRANSITION_TOOL_H
	#define TRANSITION_TOOL_H

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>










void changeState(char input, char symbols[], char transition[], int *state, int dump);
void breakValue(int *state, int breakState, int *brk);
void appendState(int *state, int breakState, char *target, char value);










#endif