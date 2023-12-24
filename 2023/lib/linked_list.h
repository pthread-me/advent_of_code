#include "main.h"

#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct _Node_{
	void* data;
	struct _Node_* next;
	struct _Node_* prev;
}Node;

typedef struct _linked_list_{
	Node* head;
	Node* tail;
	int length;
}List;

Node* node_create(void*);

List* list_create();
bool list_insert(List*, void*);
void* list_remove(List*, int(*compare)(void*, void*), void*);
bool list_insertion_sort(List*, int (*compare)(void*, void*), void*);
void print_list(List*, void(*print)(void*));

//not thread safe
void* iterator(List*);

#endif
