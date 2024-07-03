#ifndef DATA_STRUCTURES_H
	#define DATA_STRUCTURES_H



#include <stdio.h>
#include <stdlib.h>





typedef struct token {char name[33]; token *next;} token;

typedef struct Queue
{
	int n, pos;

	token *m; token *head; token *temp; token *trav;



	void (queue)(struct Queue *q, char str[]);
	void (clear_queue)(struct Queue *q);

	int (get_index)(struct Queue *q, char str[]);
	char (*get_value)(struct Queue *q, int index);

	void (show_current)(struct Queue *q);
	void (show_all)(struct Queue *q);

} Queue;





#endif