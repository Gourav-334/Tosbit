#ifndef ENCRYPTER_H
	#define ENCRYPTER_H

#define TOTAL_CHARS 95
#define MAX_OUTPUT_SIZE 93



#include <stdio.h>
#include <string.h>

#include "utility_box.c"



const char keyboard_chars[TOTAL_CHARS];
const char *prime_arr[TOTAL_CHARS];

char *encrypt(char *input);
char *decrypt(char *input);


#endif