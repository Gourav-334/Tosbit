/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef ENCRYPTER_H
	#define ENCRYPTER_H

#define TOTAL_CHARS 95
#define MAX_ENCRYPTED_SIZE 133
#define MAX_DECRYPTED_SIZE 33



#include <stdio.h>
#include <string.h>

#include "utility_box.c"










/* Encryption & decryption functions */

extern char *encrypt(char *input);
extern char *decrypt(char *input);
extern char keymapped(char *input);


#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */