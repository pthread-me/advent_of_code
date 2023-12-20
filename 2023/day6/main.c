#include "main.h"

int main(){
	
	FILE* file = fopen("input", "r");
	size_t size =0;
	char** input = calloc(2, sizeof(char*));	
	char** time = calloc(4, sizeof(int));
 	char** distance = calloc(4, sizeof(int));
	int* counter = calloc(4, sizeof(int));
	int margin = 1;
	int chars =0;

	for(int i=0; (chars = getline(&input[i], &size, file)) >0; i++){
		
		//removing the \n at the end on each line
		input[i][chars-1] = '\0';			
	}	
	fclose(file);
	

	char* save_pointer1;
	char* save_pointer2;

	//skip category text
	strtok_r(input[0], " ", &save_pointer1);	
	strtok_r(input[1], " ", &save_pointer2);	

	
	for(int i=0; i<4; i++){
		time[i] = strtok_r(NULL, " ", &save_pointer1);
		distance[i] = strtok_r(NULL, " ", &save_pointer2);
		
	}

	for(int i=1; i<4; i++){
		time[0] = strcat(time[0], time[i]);
		distance[0] = strcat(distance[0], distance[i]);
	}

	long t = strtol(time[0], NULL, 10);
	long d = strtol(distance[0], NULL, 10);
	
	printf("%ld\t%ld\n", t,d);

	for(int i=0; t-i>0; i++){
		if(i* (t-i)>d){
			printf("%ld", t-(i-1) -i);
			break;
		}
	}
}
