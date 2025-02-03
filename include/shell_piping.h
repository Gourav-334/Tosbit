#ifndef SHELL_PIPING
	#define SHELL_PIPING

#define FALSE 0
#define TRUE 1

#define LOC_MAX_LENGTH 17



#include <stdio.h>
#include "utility_box.h"





/* Variables */

extern char loc[LOC_MAX_LENGTH];



/* Functions */

extern void recordLog(char username[], char command[]);
extern void getLocation();





#endif