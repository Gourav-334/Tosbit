/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef ENCRYPTER_H
	#define ENCRYPTER_H


#define TOTAL_CHARS 		95  		// Total characters available on keyboard.
#define MAX_ENCRYPTED_SIZE 	133  		// Limit size for an encrypted string.
#define MAX_DECRYPTED_SIZE 	33  		// Limit size for a decrypted string.





#include "utility_box.h"		// Custom utility functions header.










/* Encryption & decryption functions */

extern char *encrypt(char *input);			// Encrypts the passed argument string.
extern char *decrypt(char *input);			// Decrypts the passed argument string.
extern char keymapped(char *input);  		// Tells the equivalent mapped code for a key.










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */