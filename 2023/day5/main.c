#include "main.h"


Map** create_map(){
	Map** map = calloc(7, sizeof(Map*));

	for(int i=0; i<7;i++){
		map[i] = calloc(1, sizeof(Map));

		map[i]->src_start = calloc(MAX_MAP_SIZE, sizeof(long));
		map[i]->src_end = calloc(MAX_MAP_SIZE, sizeof(long));
		map[i]->des_start = calloc(MAX_MAP_SIZE, sizeof(long));
		map[i]->des_end = calloc(MAX_MAP_SIZE, sizeof(long));
		map[i]->map_size = 0;
	}
	
	return map;
}


long map_stack_check(Map** map, long current){
	long location = current;
	bool found = false;

	for(int i=5; i>-1; i--){
		found = false;
		for(int j=0; j<map[i]->map_size; j++){
			if(location <= map[i]->des_end[j] && location >=map[i]->des_start[j]){
				location = map[i]->src_start[j] + (location - map[i]->des_start[j]);
				found = true;
				if(i==0){
					return location;
				}
				break;
			}
		}
		if(!found){
			break;
		}
	}
	return -1;
}


int main(){

	FILE* input = fopen("./input", "r");

	size_t getline_size=0;
	char* line;
	int chars_read;
	char* token;
	long current_num;

	Map** map = create_map(); 
	long seeds[] = {[0 ... NUMBER_OF_SEEDS -1] = -1};	

	//reading seeds
	getline(&line, &getline_size, input);
	strtok(line, &delim);
	for(int i=0; (token = strtok(NULL, &delim)) != NULL; i++){
		current_num = strtol(token, NULL, base);
		seeds[i] = current_num;
	}

	//empty line
	getline(&line, &getline_size, input);

	for(int m=0; m<7; m++){

		getline(&line, &getline_size, input);

		for(int i=0; (chars_read = getline(&line, &getline_size, input))>1; i++){
			line[chars_read-1] = '\0';
	
			token = strtok(line, &delim);
			map[m]->des_start[i] = strtol(token, NULL, base); 

			token = strtok(NULL, &delim);
			map[m]->src_start[i] = strtol(token, NULL, base); 
	
			token = strtok(NULL, &delim);
			current_num = strtol(token, NULL, base) -1; 

			map[m]->des_end[i] = map[m]->des_start[i] + current_num;
			map[m]->src_end[i] = map[m]->src_start[i] + current_num;
			map[m]->map_size+=1;	
		}
	}



	//bubble sort (i think)
	for(int i=0; i<map[6]->map_size; i++){
		int min_index = i;
		
		for(int j=i; j<map[6]->map_size; j++){
			min_index = map[6]->des_start[min_index] > map[6]->des_start[j] ? j : min_index; 	
		}

		if(min_index != i){
			int temp_src_start = map[6]->src_start[i];
			int temp_src_end = map[6]->src_end[i];
			int temp_des_start = map[6]->des_start[i];
			int temp_des_end = map[6]->des_end[i];

			map[6]->src_start[i] = map[6]->src_start[min_index];
			map[6]->src_end[i] = map[6]->src_end[min_index];
			map[6]->des_start[i] = map[6]->des_start[min_index];
			map[6]->des_end[i] = map[6]->des_end[min_index];
	
			map[6]->src_start[min_index] = temp_src_start;
			map[6]->src_end[min_index] = temp_src_end;
			map[6]->des_start[min_index] = temp_des_start;
			map[6]->des_end[min_index] = temp_des_end;
		}
	} 	

	long min;

	for(int i=0; i<map[6]->map_size; i++){
		for(long j=map[6]->des_start[i]; j<map[6]->des_end[i]; j++){
			
			int offset = j-map[6]->des_start[i];
						
			if( (min = map_stack_check(map, map[6]->src_start[i] + offset)  > -1)){
				
				printf("%ld with:\n %ld", min, j);
				break;
			}
		}
	}

}
