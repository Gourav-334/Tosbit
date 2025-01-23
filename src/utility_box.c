/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "utility_box.h"





/* Appends string to another string */

void strappend(char str[], char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[strlen(str)] = addition[i];
		//printf("%d-%c-%s\n", i, addition[i], str);
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

int illegalChars(char arr[], char chars[])
{
	int brk = FALSE;

	for (int i=0; i<strlen(chars); i++)
	{
		for (int j=0; j<strlen(arr); j++)
		{
			if (arr[j]==chars[i])
			{
				return TRUE;
			}
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





/* Removes whitespaces from a string from both the sides. (provide a buffer too.) */

extern void spaceRemover(char str[], char result[], int size)
{
	int start, end;

	for (int i=0; i<strlen(str); i++) {if (str[i]!=' ') {start = i; break;}}
	for (int i=strlen(str)-1; i>=0; i--) {if (str[i]!=' ') {end = i; break;}}
	for (int i=start; i<=end; i++) {result[strlen(result)] = str[i];}
}





/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */