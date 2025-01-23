/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef QUEUE_H
	#define QUEUE_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "utility_box.h"










/* Variables */

extern char node_value[33];



/* The structure containing Queue node's instructions */

typedef struct node {char name[33]; struct node *next;} node;



/* Queue class with all related functions */

typedef struct Queue
{
	int n, pos;
	struct node *m, *head, *temp, *trav;


	void (*queue)(struct Queue *q, char str[]);
	void (*clear)(struct Queue *q);
	int (*getIndex)(struct Queue *q, char str[]);
	char *(*getValue)(struct Queue *q, int index);
	void (*peek)(struct Queue *q);
	void (*showAll)(struct Queue *q);

} Queue;





/* Queue class methods */

extern void Queue_queue(Queue *q, char str[]);
extern void Queue_clear(Queue *q);

extern int Queue_getIndex(Queue *q, char str[]);
extern char *Queue_getValue(Queue *q, int index);

extern void Queue_peek(Queue *q);
extern void Queue_showAll(Queue *q);





#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */
