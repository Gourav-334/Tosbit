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





/* Remove spaces from the input string */

void remove_spaces(char str[])
{
	int fill_mode = FALSE, index;

	for (int i=0; i<strlen(str); i++)	//i, index, fill_mode, str[i], str
	{
		if (fill_mode==FALSE)
		{
			if (str[i]==' ')
			{
				index = i; fill_mode = TRUE;
			}
		}


		else if (fill_mode==TRUE)
		{
			if (str[i]!=' ')
			{
				str[index] = str[i]; str[i] = ' ';
				i = index; fill_mode = FALSE;
			}
		}
	}


	index = strlen(str) - 1;


	while (str[index]==' ')
	{
		memset((str + index), 0, sizeof(char));
		index--;
	}
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