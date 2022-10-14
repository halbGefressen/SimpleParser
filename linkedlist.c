#pragma warning(disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"


void _print_list(node *head) {
	if (!head) {
		printf("        NULL          \n");
		return;
	}
	printf("--------------------\n");
	printf("|");
	if(head->elem) {
		printf("      %s        ", head->elem);
	}
	printf("|\n");
	printf("--------------------\n");
	printf("         |          \n");
	_print_list(head->next);
}

/**
* prints the linked list to stdout
*/
int print_list(linkedlist *ll) {
	if (!ll) {
		return EXIT_FAILURE;
	}
	printf("Printing List:\n");
	_print_list(ll->head);
	return EXIT_SUCCESS;
}


int _list_add(linkedlist *ll, node *head, char *elem) {
	if (!ll) {
		return EXIT_FAILURE;
	}
	//empty list
	if (!head) {
		node* new = (node*)malloc(sizeof(node));
		if (!new) {
			return EXIT_FAILURE;
		}
		new->next = NULL;
		strncpy(new->elem, elem, MAX_LIST_ELEM_SIZE);
		ll->head = new;
		return EXIT_SUCCESS;
	}

	// end of the list
	if (!head->next) {
		node* new = (node*)malloc(sizeof(node));
		if (!new) {
			return EXIT_FAILURE;
		}
		new->next = NULL;
		strncpy(new->elem, elem, MAX_LIST_ELEM_SIZE);
		head->next = new;
		return EXIT_SUCCESS;
	}
	else {
		_list_add(ll,head->next, elem);
	}
	return EXIT_FAILURE;
}

/**
* adds a new element to the end of the linked list
*/
int list_add(linkedlist *ll, char* elem) {
	if (strlen(elem) > MAX_LIST_ELEM_SIZE) {
		return EXIT_FAILURE;
	}
	if (strlen(elem) == 0) {
		return EXIT_FAILURE;
	}
	return _list_add(ll,ll->head,elem);
}

node* _list_delete(node* head, char* elem) {
	if (!head) {
		return NULL;
	}
	if (!strncmp(head->elem, elem, MAX_LIST_ELEM_SIZE)) {
		node* tmp = head->next;
		free(head);
		return tmp;
	}

	head->next = _list_delete(head->next, elem);
	return NULL;
}

/**
* deletes the element (if found)
*/
int list_delete(linkedlist* ll, char* elem) {
	if (!ll) {
		return EXIT_FAILURE;
	}

	if (sizeof(*elem) > MAX_LIST_ELEM_SIZE) {
		return EXIT_FAILURE;
	}

	if (!ll->head) {
		return EXIT_FAILURE;
	}

	//head is the element to be deleted
	if (!strncmp(ll->head->elem, elem, MAX_LIST_ELEM_SIZE)) {
		node* tmp = ll->head;
		ll->head = tmp->next;
		free(tmp);
		return EXIT_SUCCESS;
	}

	_list_delete(ll->head,elem);
	return EXIT_FAILURE;
}


/**
* creates a new empty list
*/
linkedlist* create_list() {
	linkedlist* ll = (linkedlist*)malloc(sizeof(linkedlist));
	if (!ll) {
		return NULL;
	}
	ll->head = NULL;
	return ll;
}

/**
* frees the linked list and avoids memory leaks
*/
void free_list(linkedlist *ll) {
	node* head = ll->head;
	free(ll);
	node* tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}