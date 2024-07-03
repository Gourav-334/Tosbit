#ifndef UTILITY_BOX_H
	#define UTILITY_BOX_H


#include <stdio.h>
#include <string.h>



void strappend(char str[], int *cursor_pos, char *addition);
void constrappend(char str[], int *cursor_pos, const char *addition);
void charappend(char str[], int *cursor_pos, char addition);
void const_charappend(char str[], int *cursor_pos, const char *addition);
void newline_remover(char str[]);
void frontchar_remover(char str[]);
void flush_stdin();
void binary_print(char str[], int size);
int char_in_array(char c, char arr[], int length);



#endif