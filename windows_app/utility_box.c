#ifndef UTILITY_BOX_C
	#define UTILITY_BOX_C


#include "utility_box.h"





// 1) Appends string to another string.

void strappend(char str[], int *cursor_pos, char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[i + (*cursor_pos)] = addition[i];
	}

	*cursor_pos += strlen(addition);
}





// 2) Appends contant string to another string.

void constrappend(char str[], int *cursor_pos, const char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[i + (*cursor_pos)] = addition[i];
	}

	*cursor_pos += strlen(addition);
}





// 3) Appends character to a string.

void charappend(char str[], int *cursor_pos, char addition)
{
	str[*cursor_pos] = addition;

	*cursor_pos += sizeof(char);
}





// 4) Appends constant character to a string.

void const_charappend(char str[], int *cursor_pos, const char *addition)
{
	str[*cursor_pos] = *addition;

	*cursor_pos += sizeof(char);
}





// 5) Removes newline from a string.

void newline_remover(char str[])
{
	if (str[strlen(str)-1]=='\n')
	{
		memset((str+(strlen(str)-1)), 0, sizeof(char));
	}
}





void frontchar_remover(char str[])
{
	memset(str, 0, 1*sizeof(char));
}





// 6) Cleans the standard input buffer.

void flush_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}





void binary_print(char str[], int size)
{
	for (int i=0; i<size; i++)
	{
		if (str[i]=='\n') {printf("%c", '$');}

		else if (str[i]=='\0') {printf("%c", '-');}

		else {printf("%c", str[i]);}
	}

	printf("%c", '\n');
}





int char_in_array(char c, char arr[], int length)
{
	for (int i=0; i<length; i++)
	{
		if (c==arr[i]) {return 1;}
	}

	return 0;
}





#endif	//Drink mango juice after this code.