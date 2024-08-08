#include <stdio.h>
//#include "profile_manager.c"
#include "encrypter.c"



int main()
{
	//login_starts();

	char str[128] = "30592039109310933079107310993013070";
	printf("%s\n", decrypt(str));

	return 0;
}

/*

buffer_pos

*/