#include <stdio.h>
#include "data_structures.c"



int main()
{
	Queue q = {.n=0, .pos=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};

	Queue_queue(&q, "Gourav");
	Queue_queue(&q, "Deepanjan");
	Queue_queue(&q, "Atharv");
	Queue_queue(&q, "Ankit");
	Queue_queue(&q, "Anirudh");
	Queue_queue(&q, "Bhairav");

	Queue_all_node(&q);

	printf("Index: %s\n", Queue_get_value(&q, 2));
	
	Queue_clear(&q);
	Queue_current_node(&q);

	return 0;
}
