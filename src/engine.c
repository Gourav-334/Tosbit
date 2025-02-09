/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"
#include "../include/driver_manager.h"





int main(int argc, char **argv[])
{
	//profileManager();
	//getLocation();
	setConnection("123.141.138.013", "Gourav", "tangible%troops88");
	//syntaxParser("Gourav", NULL);

	interpret("open db mydb");
	interpret("push to tester(1, Dipayan)");
	interpret("push to tester(2, Arindam)");
	interpret("push to tester(3, Gourav)");

	return 0;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */