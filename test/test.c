#include <stdio.h>
#include "../include/driver_manager.h"

int main()
{
	setConnection("Gourav", "tosbit_user", "Gouraarav", 8080, "Gourav", "tosbit_user", FALSE);
	interpret("@ This is a comment @");
	endConnection();

	printf("Hello, World!\n");

	return 0;
}