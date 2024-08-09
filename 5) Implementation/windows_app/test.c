#include <stdio.h>
//#include "profile_manager.c"
#include "encrypter.c"



int main()
{
	//login_starts();

	char str[128] = "30592039109310933079107310993013070";
	printf("%s\n", decrypt(str));



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