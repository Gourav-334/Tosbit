#ifndef DATA_STRUCTURES_C
	#define DATA_STRUCTURES_C





#include "data_structures.h"




















/*

Queue behaviour:

- 'm' is the newly created node.
- 'head' is at the first node.
- 'temp' is at the last node.
- 'trav' is at the first node.

*/




















//2) Queue the given token/string to our queue. head

void Queue_queue(Queue *q, char str[])
{
	if ((q -> n)==0)
	{
		q -> m = (node*)malloc(sizeof(node));		//'m' might be something else
		q -> head = q -> m;
		q -> temp = q -> m;

		strcpy(q -> head -> name, str);

		q -> head -> next = NULL;
		q -> trav = q -> m;

		(q -> n)++;
	}


	else
	{
		q -> m = (node*)malloc(sizeof(node));
		strcpy(q -> m -> name, str);

		q -> temp -> next = q -> m;
		q -> m -> next = NULL;
		q -> temp = q -> m;

		(q -> n)++;
	}
}





// 3) Clear whole queue (freeing whole structure)

void Queue_clear(Queue *q)
{
	while ((q -> n)!=0)
	{
		q -> trav = q -> trav -> next;
		free(q->head);
		q -> head = q -> trav;

		(q -> n)--;
	}
}





// 4) Fetch index number for a string argument.

int Queue_get_index(Queue *q, char str[])
{
	q -> pos = 0;

	while (strcmp(q->trav->name,str))
	{
		q -> trav = q -> trav -> next;
		q -> pos++;
	}

	q -> trav = q -> head;

	return q -> pos;
}





// 5) Fetch string for an index as argument.

char *Queue_get_value(Queue *q, int index)
{
	char *data;			// TO BE REPAIRED...

	for (int i=0; i<index; i++) {q -> trav = q -> trav -> next;}

	strcpy(data, q->trav->name);
	q -> trav = q -> head;

	return data;		// warning: function returns address of local variable
}





// 6) Shows last node of a queue.

void Queue_current_node(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("----------------------------------\n");
		printf("Name: %s\nNext: %x\n", q->temp->name, q->temp->next);
		printf("----------------------------------\n");
	}
}





// 7) Shows all the nodes of a queue.

void Queue_all_node(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("----------------------------------\n");

		while (q->trav->next!=NULL)
		{
			printf("Name: %s\nNext: %x\n", q->trav->name, q->trav->next);
			q -> trav = q -> trav -> next;

			printf("----------------------------------\n");
		} printf("Name: %s\nNext: %x\n", q->trav->name, q->trav->next);

		printf("----------------------------------\n");

		q -> trav = q -> head;
	}
}

















#endif