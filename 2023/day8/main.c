#include "day8.h"

const char* file_name = "input";

Node* create_node(char* name, char* left_name, char* right_name){
	Node* node = calloc(1, sizeof(Node));

	node->name = calloc(1, sizeof(char*));
	node->left_name = calloc(1, sizeof(char*));
	node->right_name = calloc(1, sizeof(char*));

	node->left = NULL;
	node->right = NULL;

	strcpy(node->name, name);
	strcpy(node->left_name, left_name);
	strcpy(node->right_name, right_name);


	return node;
}

Graph* create_graph(){
	Graph* graph = calloc(1, sizeof(Graph));
	graph->path = calloc(1, sizeof(char*));
	graph->start = NULL;
	graph->end = NULL;

	return graph;
}


int main(){

	size_t line_size =0;
	int line_num =0;
	char* line;
	int chars_read =0;

	FILE* input = fopen(file_name, "r");

	getline(&line, &line_size, input);
	getline(&line, &line_size, input);

	while(getline(&line, &line_size, input) > 0){
		line_num ++;
	}
	fclose(input);
	
	input = fopen(file_name, "r");	
	char* path;
	int loop_modulo = getline(&path, &line_size, input) -1;
	
	Graph* graph = create_graph();
	graph->path = path;
	getline(&line, &line_size, input);	
	
	Node** node_list = calloc(line_num, sizeof(Node*));
	printf("%d\n", line_num);

	for(int i=0; i<line_num; i++){
	
		chars_read = getline(&line, &line_size, input);
		line[chars_read -1] = '\0';

		char* source = strtok(line, " ");
		strtok(NULL, " ");
		char* left = strtok(NULL, " ");
		char* right = strtok(NULL, " ");

		//yes i know, its leaking memory. idgaf, just like how she doesnt care about me :(
		left++;
		left[strlen(left) -1] = '\0';
		right[strlen(right) -1] = '\0';

		node_list[i] = create_node(source, left, right); 		
	}

	//setting the left/right nodes for each node
	for(int i=0; i<line_num; i++){
		for(int j=0; j<line_num && (node_list[i]->left == NULL || node_list[i]->right == NULL); j++){
			
			if(strcmp(node_list[i]->left_name, node_list[j]->name) ==0 ){
				node_list[i]->left = node_list[j];
			}
			if(strcmp(node_list[i]->right_name, node_list[j]->name) ==0 ){
				node_list[i]->right = node_list[j];
			}
		}
	}

	for(int i=0; i<line_num; i++){
		if(strcmp(node_list[i]->name, "AAA") == 0){
			graph->start = node_list[i];


		}
	}
	Node* cur = graph->start;
	char next;

	for(int i=0; strcmp(cur->name, "ZZZ") !=0; i++){
		printf("i is %d\tloopback=%d\tchar is %c\n", i, i%loop_modulo, graph->path[i%loop_modulo]);
		
		next = graph->path[i % loop_modulo];

		if(next == 'R'){
			cur = cur->right;
		}else{
			cur = cur->left;
		}
		graph->size++;
	}

	printf("%d\n", graph->size);


}
