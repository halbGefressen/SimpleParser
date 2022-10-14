#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifndef MAX_LIST_ELEM_SIZE
#define MAX_LIST_ELEM_SIZE 128
#endif

typedef struct node_t {
	char elem[MAX_LIST_ELEM_SIZE];
	struct node_t* next;
} node;

typedef struct linkedlist_t {
	node* head;
} linkedlist;

int print_list(linkedlist* ll);
int list_add(linkedlist* ll, char* elem);
linkedlist* create_list();
void free_list(linkedlist* ll);
int list_delete(linkedlist* ll, char* elem);
#endif