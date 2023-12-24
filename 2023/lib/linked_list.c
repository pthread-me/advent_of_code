#include "linked_list.h"

List* iter_list = NULL;
Node* iter_cur =NULL;

Node* node_create(void* data){
	if(data==NULL){
		printf("data in node_create is NULL\n");
		exit(-1);
	}

	Node* node = calloc(1, sizeof(Node));
	
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	
	return node;
}

List* list_create(){
	List* list = calloc(1, sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;

	return list;
}

bool list_insert(List* list, void* data){
	if(list == NULL || data == NULL){
		printf("NULL linked list or NULL data, in list_insert\n");
		exit(-1);
	}

	Node* node = node_create(data);

	if(list->head == NULL){
		list->head = node;
		list->tail = node;
		list->length++;
		return true;
	}

	node->prev = list->tail;
	list->tail->next = node;
	list->tail = node;
	list->length++;
	return true;
}


void* list_remove(List* list, int(*compare)(void*, void*) ,void* data){
	if(list==NULL, data==NULL){
		printf("NULL linked list or NULL data, in list_remove\n");
		exit(-1);
	}else if(list->head==NULL || list->tail==NULL){
		printf("removing from an empty list\n");
		exit(-1);
	}

	Node* to_remove = NULL; 
	bool found = false;

	if(	compare(list->head->data, data)	== 0){
		to_remove = list->head;
		list->head = to_remove->next;
		to_remove->next = NULL;
		found = true;

	}else if( compare(list->tail, data)	== 0){
		to_remove = list->tail;
		list->tail = to_remove->prev;
		list->tail->next = NULL;
		to_remove->prev = NULL;
		found = true;
	}else{
		Node* cur = list->head->next;
		while(cur != NULL){
			if(compare(cur->data, data) == 0){
				to_remove = cur;
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				cur->next = NULL;
				cur->prev = NULL;
				found = true;
			}
		}
	}

	if(found){
		list->length--;
		return to_remove->data;
	}
	return NULL;
}

void print_list(List* list, void(*print)(void*)){
	if(list==NULL || list->head==NULL){
		printf("printing NULL list\n");
		exit(-1);
	}

	Node* cur = list->head;
	while(cur!=NULL){
		print(cur->data);
		cur = cur->next;
	}
}

bool list_insertion_sort(List* list, int(*compare)(void*, void*), void* data){
	if(list==NULL || data==NULL){
		printf("insertion sort on a NULL list or data");
		exit(-1);
	}

	Node* new = node_create(data);
	Node* cur = list->head;

	if(cur==NULL){
		list->head = new;
		list->tail = new;
		list->length++;
		return true;
	}
	
	while(cur != NULL ){
		if(compare(data, cur->data) <0 ){
			if(cur == list->head){
				new->next = cur;
				cur->prev = new;
				list->head = new;
				list->length++;
				return true;
			}else{
				cur->prev->next = new;
				new->prev = cur->prev;

				cur->prev = new;
				new->next = cur;
				list->length++;
				return true;
			}
		}
			cur = cur->next;
	}
	list_insert(list, data);
}


void* iterator(List* list){

		if(list == NULL){
			printf("NULL List*\n");
			exit(-1);
		} else if(list->head == NULL){
			printf("iterating over an empty list\n");
			exit(-1);
		}

	if(iter_list == NULL || iter_list != list){
		iter_list = list;
		iter_cur = list->head;
	}



	if(iter_cur == NULL){
		iter_list == NULL;
		return NULL;
	}

	void* data = iter_cur->data;
	iter_cur = iter_cur->next;

	return data;
}
