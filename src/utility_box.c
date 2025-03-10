/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/utility_box.h"





/* Appends string to another string */

void strappend(char str[], char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[strlen(str)] = addition[i];
	}
}





/* Appends contant string to another string */

void constrappend(char str[], const char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[strlen(str)] = addition[i];
	}
}





/* Appends character to a string */

void charappend(char str[], char addition)
{
	str[strlen(str)] = addition;
}





/* Appends constant character to a string */

void const_charappend(char str[], const char addition)
{
	str[strlen(str)] = addition;
}





/* Removes newline from a string */

void newline_remover(char str[])
{
	if (str[strlen(str)-1]=='\n')
	{
		memset((str+(strlen(str)-1)), 0, sizeof(char));
	}
}





/* Removes first character from the string */

void frontchar_remover(char str[])
{
	memset(str, 0, 1*sizeof(char));
	(*str)++;
}





/* BRAINF*CK WARNING!: Cleans the standard input buffer */

void flush_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}





/* Print whole string transparently */

void binary_print(char str[], int size)
{
	for (int i=0; i<size; i++)
	{
		if (str[i]=='\n') {printf("%c", '$');}			// For newlines

		else if (str[i]=='\0') {printf("%c", '-');}		// For string terminators

		else {printf("%c", str[i]);}					// Otherwise
	}

	printf("%c", '\n');
}





/* Shift characters of a string in a particular direction by some steps */

void str_shift(char str[], int start, int end, int direction, int steps)
{
	for (int i=start; i<=end; i++)
	{
		printf("%c, %d\n", str[i], i+(direction*steps));
		str[i+(direction*steps)] = str[i];
	}


	if (direction==-1)
	{
		for (int i=end+1; i<strlen(str); i++) {memset((str+end-steps), 0, strlen(str)-(end+steps));}
	}
}





/* Check existence of a character in an array */

int illegalChars(char str[], char chars[])	// Might become problem of the future.
{
	int brk = FALSE;

	for (int i=0; i<strlen(str); i++)
	{
		for (int j=0; j<strlen(chars); j++)
		{
			if (str[i]==chars[j])
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}





int illegalChar(char character, char chars[])	// Might become problem of the future too.
{
	int brk = FALSE;

	for (int i=0; i<strlen(chars); i++)
	{
		if (character==chars[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}





/* Makes use of 'feof()' function safer. */

int reachedEOF(FILE *fptr)
{
	int c = fgetc(fptr);

	if (feof(fptr)) {fseek(fptr, -1, SEEK_CUR); return TRUE;}
	else if (!feof(fptr)) {fseek(fptr, -1, SEEK_CUR); return FALSE;}
}





/* Checks if a file is new (0 bytes) or already in use. */

int newFile(FILE *fptr)
{
	int position = ftell(fptr);

	fseek(fptr, 0, SEEK_SET);

	if (reachedEOF(fptr)) {fseek(fptr, position, SEEK_SET); return TRUE;}
	else if (!reachedEOF(fptr)) {fseek(fptr, position, SEEK_SET); return FALSE;}
}





/* Removes whitespaces from a string from both the sides. (provide a buffer too.) */

extern void spaceRemover(char str[], char result[], int size)
{
	int start, end;

	for (int i=0; i<strlen(str); i++) {if (str[i]!=' ') {start = i; break;}}
	for (int i=strlen(str)-1; i>=0; i--) {if (str[i]!=' ') {end = i; break;}}
	for (int i=start; i<=end; i++) {result[strlen(result)] = str[i];}
}





/* Makes an attribute name independent of its key symbol. */

void removeKeySymbol(char *attribute)
{
	if (attribute[0]=='$' || attribute[0]=='#')
	{
		for (int i=0; i<strlen(attribute)-1; i++)
		{
			attribute[i] = attribute[i+1];
		}

		memset((attribute + strlen(attribute) - 1) , 0, sizeof(char));
	}
}





/* Integer to ASCII conversion. */

char *itoa(int x, char *ascii)
{
	snprintf(ascii, sizeof(ascii), "%d", x);

	return ascii;
}





/* Adds endline terminator at the end of a string. */

char *addTerminator(char *str)
{
	str[strlen(str)] = '\0';

	return str;
}





/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */