/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef UTILITY_BOX_H
	#define UTILITY_BOX_H



#define FALSE 	0  		// Macro to imitate boolean FALSE behaviour.
#define TRUE 	1  		// Macro to imitate boolean TRUE behaviour.





#include <stdio.h>			// Standard input/output header.
#include <string.h>			// String utility header.










/* Funtions declarations (most are related to string manipulation) */

extern void strappend(									// Appends string to another string.
	char str[], char *addition
);
extern void constrappend(								// Appends contant string to another string.
	char str[], const char *addition
);
extern void charappend(									// Appends character to a string.
	char str[], char addition
);
extern void const_charappend(							// Appends constant character to a string.
	char str[], const char addition
);
extern void newline_remover(char str[]);				// Removes newline from a string.
extern void frontchar_remover(char str[]);				// Removes first character from the string.
extern void flush_stdin();								// Cleans the standard input buffer.
extern void binary_print(char str[], int size);			// Print whole string transparently.
extern void str_shift(									// Shift characters of a string in a particular direction by some steps.
	char str[],
	int start, int end,
	int direction, int steps
);
extern int illegalChars(								// Check existence of some characters in an array.
	char str[], char chars[]
);
extern int illegalChar(									// Check existence of a character in an array.
	char character, char chars[]
);
extern int reachedEOF(FILE *fptr);						// Makes use of 'feof()' function safer.
extern int newFile(FILE *fptr);							// Checks if a file is new (0 bytes) or already in use.
extern void spaceRemover(								// Removes whitespaces from a string from both the sides (provide a buffer too).
	char str[], char result[],
	int size
);
extern void removeKeySymbol(char *attribute);			// Makes an attribute name independent of its key symbol.
extern char *itoa(int x, char *ascii);					// Integer to ASCII conversion.
extern char *addTerminator(char *str);					// Adds string terminator at the end of a string.
extern void printRaw(char *str);						// Prints characters as raw.










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */