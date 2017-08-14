#include "Item.c"

typedef struct node {
	/*
	item - contains the value of the current cell.
	next - a pointer to the next node.
	previous - a pointer to the previous node.
	*/
	item_t* item;
	struct node *next;
	struct node *previous;
} node_t;