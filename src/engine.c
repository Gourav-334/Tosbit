/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/profile_manager.h"
#include "../include/driver_manager.h"





int main(int argc, char **argv[])
{
	//profileManager();
	//getLocation();
	setConnection("123.141.138.013", "Gourav", "tangible%troops88");
	
	interpret("OPEN DB mydb");
	interpret("DELETE TABLE destiny");
	interpret("MAKE TABLE destiny(STRING name, FLOAT ego)");
	interpret("SHOW STRUCT destiny");

	return 0;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */