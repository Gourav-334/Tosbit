#ifndef DATA_STRUCTURES_H
	#define DATA_STRUCTURES_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>










// Size variables
//int Queue_n_size = 48;





typedef struct token {char name[33]; struct token *next;} token;





typedef struct Queue
{
	//struct token node;



	int n, pos;

	struct token *m, *head, *temp, *trav;



	void (*Queue_queue)(struct Queue *q, char str[]);
	void (*Queue_clear)(struct Queue *q);
	int (*Queue_get_index)(struct Queue *q, char str[]);
	char *(*Queue_get_value)(struct Queue *q, int index);
	void (*Queue_current_node)(struct Queue *q);
	void (*Queue_all_node)(struct Queue *q);

} Queue;





void Queue_queue(Queue *q, char str[]);
void Queue_clear(Queue *q);

int Queue_get_index(Queue *q, char str[]);
char *Queue_get_value(Queue *q, int index);

void Queue_current_node(Queue *q);
void Queue_all_node(Queue *q);





#endif