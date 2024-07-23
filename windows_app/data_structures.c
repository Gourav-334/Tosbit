#ifndef DATA_STRUCTURES_C
	#define DATA_STRUCTURES_C





#include "data_structures.h"




















/*

Offset sizes (Queue members):

int 	n: 				48
int 	pos: 			52
struct 	Queue *m: 		56
struct 	Queue *head: 	64
struct 	Queue *temp: 	72
struct 	Queue *trav: 	80

struct 	Size: 			88 bytes


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
		q -> m = (token*)malloc(sizeof(token));		//'m' might be something else
		q -> head = q -> m;
		q -> temp = q -> m;

		strcpy(q -> head -> name, str);

		q -> head -> next = NULL;

		(q -> n)++;
	}


	else
	{
		q -> m = (token*)malloc(sizeof(token));
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
		q -> temp = q -> head;
		q -> head = q -> head -> next;
		free(q -> temp);
		q -> temp = q -> head;

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
	char data[33] = {0};

	for (int i=0; i<index; i++) {q -> trav = q -> trav -> next;}

	strcpy(data, q->trav->name);
	q -> trav = q -> head;

	return data;
}





// 6) Shows last node of a queue.

void Queue_current_node(Queue *q)
{
	printf("Name: %s\nNext: %x", q->temp->name, q->temp->next);
}





// 7) Shows all the nodes of a queue.

void Queue_all_node(Queue *q)
{
	while (q->trav->next!=NULL)
	{
		printf("Name: %s\nNext: %x", q->temp->name, q->temp->next);
		q -> trav = q -> trav -> next;
	} printf("Name: %s\nNext: %x", q->temp->name, q->temp->next);
}

















#endif