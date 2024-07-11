#ifndef DATA_STRUCTURES_H
	#define DATA_STRUCTURES_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>





typedef struct token {char name[33]; struct token *next;} token;





typedef struct Queue
{
	struct token;



	int n, pos;

	struct token *m, *head, *temp, *trav;



	void (*queue)(struct Queue *q, char str[]);
	void (*clear_queue)(struct Queue *q);

	int (*get_index)(struct Queue *q, char str[]);
	char *(*get_value)(struct Queue *q, int index);

	void (*show_current)(struct Queue *q);
	void (*show_all)(struct Queue *q);

} Queue;





void queue(Queue *q, char str[]);
void clear_queue(Queue *q);

int get_index(Queue *q, char str[]);
char *get_value(Queue *q, int index);

void show_current(Queue *q);
void show_all(Queue *q);





#endif