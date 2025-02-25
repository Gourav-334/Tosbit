#include "../src/queue.c"



int main()
{
	Queue q = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll,
		.changeAt = Queue_changeAt
	};


	q.queue(&q, "ABC");
	q.queue(&q, "OPQR");
	q.queue(&q, "XYZ");
	q.changeAt(&q, 1, "GHI");

	q.showAll(&q);


	return 0;
}
