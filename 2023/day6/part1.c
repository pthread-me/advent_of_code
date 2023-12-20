#include "main.h"

int main(){
	
	FILE* file = fopen("input", "r");
	size_t size =0;
	char** input = calloc(2, sizeof(char*));	
	int* time = calloc(4, sizeof(int));
 	int* distance = calloc(4, sizeof(int));
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
		time[i] = strtol( strtok_r(NULL, " ", &save_pointer1),	NULL,	10);
		distance[i] = strtol( strtok_r(NULL, " ", &save_pointer2),	NULL,	10);
		
		for(int j=0; time[i]-j >0; j++){
			if((time[i]-j) * j	> distance[i]){
				
			}
		}

		margin *= counter[i];	
	}

	printf("%d", margin);

}
