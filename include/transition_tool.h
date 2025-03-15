/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef TRANSITION_TOOL_H
	#define TRANSITION_TOOL_H



#define FALSE 	0  		// Macro to imitate boolean FALSE behaviour.
#define TRUE 	1  		// Macro to imitate boolean TRUE behaviour.





#include <stdio.h>			// Standard input/output header.
#include <stdlib.h>			// Standard library functions header.
#include <string.h>			// String utility header.










/* Functions */

extern void changeState(			// Change one state to another as per the given state & input symbol.
	char input,
	char symbols[],
	char transition[],
	int *state, int dump
);
extern void breakValue(				// Sets up the break condition as per a given state.
	int *state,
	int breakState,
	int *brk
);
extern void appendState(			// Appends a character to a given string.
	int *state,
	int breakState,
	char *target,
	char value
);
extern void limitChecker(			// Checks limit of a string & changes state and sets break value to TRUE if limit is crossed.
	char *target,
	int limit,
	int *state,
	int newState,
	int *brk
);










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */