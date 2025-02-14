/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/queue.h"




















/*

Queue behaviour:

- 'm' is the newly created node.
- 'head' is at the first node.
- 'temp' is at the last node.
- 'trav' is at the first node.

*/




















/* Variables declaration. */

char node_value[33] = {0};





/* Queue the given token/string to our queue. */

void Queue_queue(Queue *q, char str[])
{
	/* Creating a node */ 

	q -> m = (node*)malloc(sizeof(node));



	/* When inserting first node */

	if ((q -> n)==0)
	{
		q -> head = q -> m;
		q -> trav = q -> m;
	}



	/* When inserting NOT the first node */

	else {q -> temp -> next = q -> m;}



	/* Common operations, no matter whether first or any other node */

	q -> temp = q -> m;
	q -> temp -> next = NULL;		// Making next address of inserted node NULL



	/* Filling input value to node (with \0), incrementing counter & acknowledging */

	strcpy(q -> m -> name, str);
	
	q -> trav = q -> head;
	(q -> n)++;
}





/* Clear whole queue (freeing whole structure) */

void Queue_clear(Queue *q)
{
	/* Repeatedly remove a node (from head node) until no node is left */

	while ((q -> n)!=0)
	{
		q -> trav = q -> trav -> next;
		free(q->head);
		q -> head = q -> trav;

		(q -> n)--;
	}
}





/* Fetch index number for a string argument. */

int Queue_getIndex(Queue *q, char str[])
{
	/* Returning -2 incase queue is empty. */

	if (q->n==0) {return -2;}


	/* 'str2' is 'str' with null character (\0) at the end. */

	char str2[strlen(str)+1]; strcpy(str2,str);
	str2[strlen(str2)] = '\0';


	/* Starting from default position value i.e 0 */

	q -> pos = 0;


	/* Finding that node */

	while (strcmp(q->trav->name,str2) && (q->trav->next)!=NULL)
	{
		q -> trav = q -> trav -> next;
		q -> pos++;
	}


	/* Returning -1 as error status in case string value wasn't found. */

	if (strcmp(q->trav->name,str2) && (q->trav->next)==NULL) {return -1;}


	/* Throwing head back to first node */

	q -> trav = q -> head;

	return (q -> pos);
}





/* Fetch string for an index as argument */

char *Queue_getValue(Queue *q, int index)
{
	for (int i=0; i<index; i++) {q -> trav = q -> trav -> next;}

	strcpy(node_value, q->trav->name);
	q -> trav = q -> head;

	return node_value;
}





/* Shows last node of a queue. */

void Queue_peek(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("\n----------------------------------\n");
		printf("Name: %s\nNext: %p", q->temp->name, q->temp->next);
		printf("\n----------------------------------\n");
	}
}





/* Shows all the nodes of a queue */

void Queue_showAll(Queue *q)
{
	if (q->n==0) {printf("Queue is clean!\n");}

	else
	{
		printf("\n----------------------------------\n");

		while (q->trav->next!=NULL)
		{
			printf("Name: %s\nNext: %p", q->trav->name, q->trav->next);
			q -> trav = q -> trav -> next;

			printf("\n----------------------------------\n");
		} printf("Name: %s\nNext: %p", q->trav->name, q->trav->next);

		printf("\n----------------------------------\n");

		q -> trav = q -> head;
	}
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */
