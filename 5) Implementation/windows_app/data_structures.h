#ifndef DATA_STRUCTURES_H
	#define DATA_STRUCTURES_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "utility_box.c"










// Variable(s)
char node_value[33] = {0};





typedef struct node {char name[33]; struct node *next;} node;




// Queue q = {.n=0, .m=NULL, .head=NULL, .temp=NULL, .trav=NULL};


typedef struct Queue
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





void Queue_queue(Queue *q, char str[]);
void Queue_clear(Queue *q);

int Queue_getIndex(Queue *q, char str[]);
char *Queue_getValue(Queue *q, int index);

void Queue_peek(Queue *q);
void Queue_showAll(Queue *q);





#endif