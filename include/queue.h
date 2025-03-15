/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef QUEUE_H
	#define QUEUE_H



#include <stdio.h>			// Standard input/output header.
#include <string.h>			// String utility header.
#include <stdlib.h>			// Standard library functionalities header.
#include <stddef.h>			// Standard definitions header.


#include "utility_box.h"		// Custom utility functions header.










/* Variables */

extern char node_value[33];










/* The structure containing Queue node's instructions */

typedef struct node {char name[33]; struct node *next;} node;



/* Queue class with all related functions */

typedef struct Queue
{
	/* Declarations */

	/*
	 * Queue behaviour:
	 * 'm' is the newly created node.
	 * 'head' is at the first node.
	 * 'temp' is at the last node.
	 * 'trav' is at the first node.
	 */

	int n, pos;
	struct node *m, *head, *temp, *trav;



	/* Functions */

	void (*queue)(struct Queue *q, char str[]);				// Pointer to 'Queue_queue'.
	void (*clear)(struct Queue *q);							// Pointer to 'Queue_clear'.
	int (*getIndex)(struct Queue *q, char str[]);			// Pointer to 'Queue_getIndex'.
	char *(*getValue)(struct Queue *q, int index);			// Pointer to 'Queue_getValue'.
	void (*peek)(struct Queue *q);							// Pointer to 'Queue_peek'.
	void (*showAll)(struct Queue *q);						// Pointer to 'Queue_showAll'.
	void (*changeAt)(										// Pointer to 'Queue_changeAt'.
		struct Queue *q, int index, char str[]
	);

} Queue;










/* Queue class methods */

extern void Queue_queue(Queue *q, char str[]);			// Enqeues a node to the queue.
extern void Queue_clear(Queue *q);						// Dequeues a node from the queue.
extern int Queue_getIndex(Queue *q, char str[]);		// Finds index for a requested value.
extern char *Queue_getValue(Queue *q, int index);		// Fetches value from an index.
extern void Queue_peek(Queue *q);						// Peeks the top element in the queue.
extern void Queue_showAll(Queue *q);					// Prints all the elements & addresses.
extern void Queue_changeAt(								// Changes value at a given index.
	Queue *q, int index, char str[]
);










#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */