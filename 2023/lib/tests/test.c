#include "../linked_list.h"

void print(void* x){
	int* a = (int*) x;
	printf("%d\n", *a);
}

int compare(void* a, void* b){

	int* x = (int*) a;
	int* y = (int*) b;

	return *x - *y;

}

int main(){
	List* list = list_create();
	int a = 12;
	int b = 1;
	int c = 9;
	int d = 12;
	int e = 0;
	list_insert(list, &a);
	list_insert(list, &b);
	list_insert(list, &c);

	list_remove(list, compare, &d);
	print_list(list, print);
	printf("*****\ninserting 5 in between\n");

	list_insertion_sort(list, compare, &e);
	print_list(list, print);
}
