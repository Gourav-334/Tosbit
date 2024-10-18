/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef UTILITY_BOX_H
	#define UTILITY_BOX_H

#define FALSE 0
#define TRUE 1


#include <stdio.h>
#include <string.h>





/* Funtions declarations (most are related to string manipulation) */

void strappend(char str[], char *addition);
void constrappend(char str[], const char *addition);
void charappend(char str[], char addition);
void const_charappend(char str[], const char addition);
void newline_remover(char str[]);
void frontchar_remover(char str[]);
void flush_stdin();
void binary_print(char str[], int size);
void remove_spaces(char str[]);
void str_shift(char str[], int start, int end, int direction, int steps);

int char_in_array(char c, char arr[], int length);



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */