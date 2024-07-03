#ifndef DATA_STRUCTURES_C
	#define DATA_STRUCTURES_C



#include <string.h>

#include "data_structures.h"




















typedef struct token {char name[33]; token *next;} token;

typedef struct Queue
{
	int n, pos;

	token *m; token *head; token *temp; token *trav;



	void (queue)(struct Queue *q, char str[]);
	void (clear_queue)(struct Queue *q, );

	int (get_index)(struct Queue *q, char str[]);
	char (*get_value)(struct Queue *q, int index);

	void (show_current)(struct Queue *q, );
	void (show_all)(struct Queue *q, );

} Queue;





// 2) Queue the given token/string to our queue.

void queue(struct Queue *q, char str[])
{
	if (n==0)
	{
		m = (token*)malloc(sizeof(token));
		head = m; temp = m;

		strcpy(head -> name, str);

		head -> next = NULL;

		n++;
	}


	else
	{
		m = (token*)malloc(sizeof(token));
		strcpy(m -> name, str);

		temp -> next = m; m -> next = NULL;
		temp = m;

		n++;
	}
}





// 3) Clear whole queue (freeing whole structure)

void clear_queue(struct Queue *q)
{
	while (n!=0)
	{
		temp = head; head = head -> next;
		free(temp); temp = head;

		n--;
	}
}





// 4) Fetch index number for a string argument.

int get_index(struct Queue *q, char str[])
{
	pos = 0;

	while (strcmp(trav->name,str))
	{
		trav = trav -> next;
		pos++;
	}

	trav = head;

	return pos;
}





// 5) Fetch string for an index as argument.

char *get_value(struct Queue *q, int index)
{
	char data[33] = {0};

	for (int i=0; i<index; i++) {trav = trav -> next;}

	strcpy(data, trav->name); trav = head;

	return data;
}





// 6) Shows last node of a queue.

void show_current(struct Queue *q)
{
	printf("Name: %s\nNext: %x", temp->name, temp->next);
}





// 7) Shows all the nodes of a queue.

void show_all(struct Queue *q)
{
	while (trav->next!=NULL)
	{
		printf("Name: %s\nNext: %x", temp->name, temp->next);
		trav = trav -> next;
	} printf("Name: %s\nNext: %x", temp->name, temp->next);
}

















#endif