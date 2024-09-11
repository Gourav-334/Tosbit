#include <stdio.h>
#include "data_structures.c"



int main()
{
	Queue q = {.n=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};

	Queue_queue(&q, "Gourav"); printf("\n");
	Queue_queue(&q, "Kumar"); printf("\n");
	Queue_queue(&q, "Mallick"); printf("\n");

	Queue_showAll(&q);

	return 0;
}

