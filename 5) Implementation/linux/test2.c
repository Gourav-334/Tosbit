#include <stdio.h>
#include "queue.c"



int main()
{
	Queue q = {.n=0, .pos=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL, .queue=Queue_queue, .peek=Queue_peek};

	printf("%p\n", &q);

	q.queue(&q, "Gourav");
	q.peek(&q);


	return 0;
}