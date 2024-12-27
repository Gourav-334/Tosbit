/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef DATA_STRUCTURES_H
	#define DATA_STRUCTURES_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "utility_box.c"










/* Variables */

extern char node_value[257];



/* The structure containing Queue node's instructions */

extern typedef struct node {char name[257]; struct node *next;} node;



/* Queue class with all related functions */

extern typedef struct Queue
{
	int n, pos;
	struct node *m, *head, *temp, *trav;


	void (*Queue_queue)(struct Queue *q, char str[]);
	void (*Queue_clear)(struct Queue *q);
	int (*Queue_getIndex)(struct Queue *q, char str[]);
	char *(*Queue_getValue)(struct Queue *q, int index);
	void (*Queue_peek)(struct Queue *q);
	void (*Queue_showAll)(struct Queue *q);

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