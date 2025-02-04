/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"
#include "../include/driver_manager.h"





int main(int argc, char **argv[])
{
	//profileManager();
	getLocation();
	setConnection("123.141.138.013", "Gourav", "tangible%troops88");
	




	for (int i=0; i<100000; i++)
	{
		printf("-----------------------------------------------------------------------------\n");
		printf("%d\n", i);

		interpret("open db mydb");
		// interpret("clear table riseAgainst");

		// interpret("push to riseAgainst (1, Gourav)");
		// interpret("push to riseAgainst (2, Anirudh)");
		// interpret("push to riseAgainst (3, Dipayan)");
		// interpret("push to riseAgainst (4, Arindam)");
		// interpret("push to riseAgainst (5, Rikhish)");
		// interpret("push to riseAgainst (6, Divyang)");
		// interpret("push to riseAgainst (7, Deepanjan)");
		// interpret("push to riseAgainst (8, Abhay)");
		// interpret("push to riseAgainst (9, Vikas Sir)");
		// interpret("push to riseAgainst (10, Bhairav)");
	}

	return 0;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */