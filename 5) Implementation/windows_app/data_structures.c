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
		q -> head -> name[strlen(q -> head -> name)] = '\0';

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

	printf("Node \"%s\" queued!", str);
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

	printf("Whole queue cleared!\n");
}





// 4) Fetch index number for a string argument.

int Queue_getIndex(Queue *q, char str[])
{
	// 'str2' is 'str' with null character (\0) at the end.

	char str2[strlen(str)+1]; strcpy(str2,str);
	str2[strlen(str2)] = '\0';

	q -> pos = 0;

	while (strcmp(q->trav->name,str2))
	{
		q -> trav = q -> trav -> next;
		q -> pos++;
	}

	q -> trav = q -> head;

	return (q -> pos);
}





// 5) Fetch string for an index as argument.

char *Queue_getValue(Queue *q, int index)
{
	for (int i=0; i<index; i++) {q -> trav = q -> trav -> next;}

	strcpy(node_value, q->trav->name);
	q -> trav = q -> head;

	return node_value;		// warning: function returns address of local variable
}





// 6) Shows last node of a queue.

void Queue_peek(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("\n----------------------------------\n");
		printf("Name: %s\nNext: %x", q->temp->name, q->temp->next);
		printf("\n----------------------------------\n");
	}
}





// 7) Shows all the nodes of a queue.

void Queue_showAll(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("\n----------------------------------\n");

		while (q->trav->next!=NULL)
		{
			printf("Name: %s\nNext: %x", q->trav->name, q->trav->next);
			q -> trav = q -> trav -> next;

			printf("\n----------------------------------\n");
		} printf("Name: %s\nNext: %x", q->trav->name, q->trav->next);

		printf("\n----------------------------------\n");

		q -> trav = q -> head;
	}
}

















#endif