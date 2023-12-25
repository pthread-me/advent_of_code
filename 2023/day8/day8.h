#include "../lib/main.h"
typedef struct _node{
	char* name;
	char* left_name;
	char* right_name;
	struct _node* left;
	struct _node* right;
	
}Node;


typedef struct _graph{
	char* path;
	Node* start;
	Node* end;
	int size;
}Graph;

Node* create_node(char*, char*, char*);
Graph* create_graph();





