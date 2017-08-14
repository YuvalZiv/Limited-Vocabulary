#include <stdio.h>
#include "Functions.h"

#define SUCCESS 0
#define SUCCESS_MSG "SUCCESS!\n"
#define MALLOC_ERR -1
#define MALLOC_ERR_MSG "Malloc error: Unable to associate memory.\n"
#define NULL_TYPE_ERR -2
#define NULL_TYPE_ERR_MSG "NULL type error: Cannot use NULL value.\n"

list_t* create_list(void) {
	/*
	Initiate a list.
	first and last are NULL (since there are no nodes in the list).
	length and sum are both zero (ditto).
	input: void
	output: list_t*
	*/
	list_t * list = NULL;
	list = malloc(sizeof(list_t));
	if (list == NULL) {
		printf("%s", MALLOC_ERR_MSG);
		exit(MALLOC_ERR);
	}
	list->first = list->last = NULL;
	list->length = 0;
	return list;
}

void destroy_list(list_t* list) {
	/*
	Destroying a list.
	Iritate through all the nodes and free the memory.
	input: list_t*
	output: void
	*/
	if (list == NULL) {
		printf("%s", NULL_TYPE_ERR_MSG);
		exit(NULL_TYPE_ERR);
	}
	while (list->first != NULL) {
		remove_node(list, list->first);
	}
}

void add_node(list_t* list, item_t * item) {
	/*
	Adding a node to a list.
	input: list_t*, item_t*
	output: void
	*/
	if (list == NULL) {
		printf("%s", NULL_TYPE_ERR_MSG);
		exit(NULL_TYPE_ERR);
	}
	node_t* node = NULL;
	node = malloc(sizeof(node_t));
	node->item = item;
	node->next = NULL;
	node->previous = list->last;
	if (list->length == 0) {
		list->first = node;
	}
	if (list->last != NULL) {
		list->last->next = node;
	}
	list->last = node;
	list->length++;
}

void remove_node(list_t* list, node_t* node) {
	/*
	Removing a node from the list.
	input: list_t*, node*
	output: void
	*/
	if (list == NULL || node == NULL) {
		printf("%s", NULL_TYPE_ERR_MSG);
		exit(NULL_TYPE_ERR);
	}
	if (list->length == 0) {
		printf("Cannot remove from an empty list.");
		return;
	}
	list->length--;
	if (list->first == node) {
		list->first = node->next;
		if (node->next != NULL) {
			node->next->previous = NULL;
		}
	}
	else {
		node->next = node->previous;
	}
	if (list->last == node) {
		list->last = node->previous;
		if (node->previous != NULL) {
			node->previous->next = NULL;
		}
	}
	else {
		node->previous = node->next;
	}
	free(node);
}

int get_length(list_t* list) {
	/*
	Returns the length of a list.
	input: list_t*
	output: int
	*/
	if (list != NULL) {
		return list->length;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}

node_t* get_first(list_t* list) {
	/*
	Returns the first node of a list.
	input: list_t*
	output: node_t*
	*/
	if (list != NULL) {
		return list->first;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}

node_t* get_last(list_t* list) {
	/*
	Returns the last node of a list.
	input: list_t*
	output: node_t*
	*/
	if (list != NULL) {
		return list->last;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}

node_t* get_next(node_t* node) {
	/*
	Returns the next node.
	input: node_t*
	output: node_t*
	*/
	if (node != NULL) {
		return node->next;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}

node_t* get_previous(node_t* node) {
	/*
	Returns the previous node.
	input: node_t*
	output: node_t*
	*/
	if (node != NULL) {
		return node->previous;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}

item_t* get_value(node_t* node) {
	/*
	Returns the value of a node.
	input: node_t*
	output: item_t*
	*/
	if (node != NULL) {
		return node->item;
	}
	printf("%s", NULL_TYPE_ERR_MSG);
	exit(NULL_TYPE_ERR);
}