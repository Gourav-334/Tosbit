/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef UTILITY_BOX_C
	#define UTILITY_BOX_C



#include "utility_box.h"





/* Appends string to another string */

void strappend(char str[], char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[strlen(str)] = addition[i];
		printf("%d-%c-%s\n", i, addition[i], str);
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





/* Check existence of a character in an array */

int char_in_array(char c, char arr[], int length)
{
	for (int i=0; i<length; i++)
	{
		if (c==arr[i]) {return 1;}
	}

	return 0;
}





#endif	//Drink mango juice after this code.



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */