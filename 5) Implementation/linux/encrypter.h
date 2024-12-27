/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef ENCRYPTER_H
	#define ENCRYPTER_H

#define TOTAL_CHARS 95
#define MAX_ENCRYPTED_SIZE 133
#define MAX_DECRYPTED_SIZE 33



#include <stdio.h>
#include <string.h>

#include "utility_box.c"





/* All possible inputs coming from STDOUT (keyboard) */

extern const char keyboard_chars[TOTAL_CHARS] = {' ','`','~','1','!','2','@','3','#','4',		//10
	'$','5','%','6','^','7','&','8','*','9','(','0',')','-','_','=','+','q','Q','w',	//30
	'W','e','E','r','R','t','T','y','Y','u','U','i','I','o','O','p','P','[','{',']',	//50
	'}','a','A','s','S','d','D','f','F','g','G','h','H','j','J','k','K','l','L',';',	//70
	':','\'','\"','z','Z','x','X','c','C','v','V','b','B','n','N','m','M',',','<',		//89
	'.','>','/','?'																		//93
};



/* Equivalent encrypted prime codes for STDOUT symbols */

extern const char *prime_codes[TOTAL_CHARS] = {
    "11", "13", "17", "19", "23", "29", "31", "37", "41", "43", "47", "53", "59",		//13
    "61", "67", "71", "73", "79", "83", "89", "97", "113", "127", "131", "137", 		//25
    "139", "149", "151", "157", "163", "167", "173", "179", "181", "191", "193", 		//36
    "197", "199", "211", "223", "227", "229", "233", "239", "241", "251", "257", 		//47
    "263", "269", "271", "277", "281", "283", "293", "311", "313", "317", "331", 		//58
    "337", "347", "349", "353", "359", "367", "373", "379", "383", "389", "397", 		//69
    "419", "421", "431", "433", "439", "443", "449", "457", "461", "463", "467", 		//80
    "479", "487", "491", "499", "521", "523", "541", "547", "557", "563", "569",		//91
    "571", "577"																		//93
};










/* Encryption & decryption functions */

extern char *encrypt(char *input);
extern char *decrypt(char *input);
extern char keymapped(char *input);


#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */