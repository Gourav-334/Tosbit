#include <stdio.h>
//#include "profile_manager.c"
#include "encrypter.c"



int main()
{
	//login_starts();

	char str[128] = "Deepanjan's Lamp";
	//

	printf("ENCRYPTED: %s\nDECRYPTED: %s\n\n\n", encrypt(str), decrypt(encrypt(str)));

	printf("HELLO, GOD!");



	// char str2[33] = {0};
	// charappend(str2,'G'); printf("%s\n", str2);
	// charappend(str2,'o'); printf("%s\n", str2);
	// charappend(str2,'u'); printf("%s\n", str2);
	// charappend(str2,'r'); printf("%s\n", str2);

	return 0;
}

/*

buffer_pos

*/