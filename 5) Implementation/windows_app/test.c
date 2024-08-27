#include <stdio.h>
#include "data_structures.c"



int main()
{
	Queue q = {.n=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};

	Queue_queue(&q, "Gourav");
	Queue_queue(&q, "Kumar");
	Queue_queue(&q, "Mallick");

	return 0;
}

