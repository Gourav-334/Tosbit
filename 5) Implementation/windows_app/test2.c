#include "transition_tool.c"


//Database Simulator?

int main()
{
	char str[55] = "Goura";
	int state = 4;
	appendChar(&state, 4, str, 'v');
	printf("STR: %s\n", str);

	return 0;
}
