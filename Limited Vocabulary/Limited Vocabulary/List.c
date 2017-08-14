#include "Node.c"

typedef struct list {
	/*
	sum - sum of all the vars in the list.
	length - how many vars in the list.
	first - pointer to the first node of the list.
	last - pointer to the last node of the list.
	*/
	int length;
	node_t *first;
	node_t *last;
} list_t;