/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef UTILITY_BOX_H
	#define UTILITY_BOX_H

#define FALSE 0
#define TRUE 1


#include <stdio.h>
#include <string.h>





/* Funtions declarations (most are related to string manipulation) */

extern void strappend(char str[], char *addition);
extern void constrappend(char str[], const char *addition);
extern void charappend(char str[], char addition);
extern void const_charappend(char str[], const char addition);

extern void newline_remover(char str[]);
extern void frontchar_remover(char str[]);

extern void flush_stdin();
extern void binary_print(char str[], int size);
extern void remove_spaces(char str[]);
extern void str_shift(char str[], int start, int end, int direction, int steps);

extern int illegalChars(char arr[], char chars[]);
extern int safeEOF(FILE *fptr);



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */