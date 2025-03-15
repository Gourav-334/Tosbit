/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef SHELL_PIPING
	#define SHELL_PIPING



#define FALSE 	0  		// Macro to imitate boolean FALSE behaviour.
#define TRUE 	1  		// Macro to imitate boolean TRUE behaviour.


#define LOC_MAX_LENGTH 17  		// Length limit for the fetched location.





#include <stdio.h>				// Standard input/output header.
#include <stdlib.h>				// Standard library functionalities header.
#include "utility_box.h"		// Custom utility functions header.










/* Variables */

extern char loc[LOC_MAX_LENGTH];		// Stores the fetched location as longitude & latitude.










/* Functions */

extern void recordLog(					// Records the log details in JSON structure.
	char username[], char command[]
);
extern void getLocation();				// Gets the location in from of longitude & latitude.










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */