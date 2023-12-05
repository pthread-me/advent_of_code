#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define base 10
#define NUMBER_OF_SEEDS 20

const char delim = ' ';

typedef struct Mapping{
	long* src_start;
	long* src_end;
	long* des_start;
	long* des_end;
}Map;

Map* create_map(){
	Map* map = calloc(1, sizeof(map));
	
	map->src_start = calloc(50, sizeof(long));
	map->src_end = calloc(50, sizeof(long));
	map->des_start = calloc(50, sizeof(long));
	map->des_end = calloc(50, sizeof(long));

	return map;
}

int main(){

	FILE* input = fopen("./input", "r");

	size_t getline_size=0;
	char* line;
	int chars_read;
	char* token;
	long current_num;

	Map* map;
	long seeds[] = {[0 ... NUMBER_OF_SEEDS-1] = -1};	

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
		map = create_map();

		getline(&line, &getline_size, input);
		for(int i=0; (chars_read = getline(&line, &getline_size, input))>1; i++){
			line[chars_read-1] = '\0';
	
			token = strtok(line, &delim);
			map->des_start[i] = strtol(token, NULL, base); 
	
			token = strtok(NULL, &delim);
			map->src_start[i] = strtol(token, NULL, base); 
	
			token = strtok(NULL, &delim);
			current_num = strtol(token, NULL, base) -1; 

			map->des_end[i] = map->des_start[i] + current_num;
			map->src_end[i] = map->src_start[i] + current_num;
		}

		for(int j=0; j<NUMBER_OF_SEEDS; j++){
			for(int k=0; k<50; k++){
				if(seeds[j] >= map->src_start[k] && seeds[j] <= map->src_end[k]){
					seeds[j] = map->des_start[k] + (seeds[j] - map->src_start[k]);

					break;
				}
			}

		}
		free(map);		
	}


	long mini = seeds[0];
	for(int i=0; i<NUMBER_OF_SEEDS; i++){
		mini = seeds[i]<mini?seeds[i]:mini;
	}

	printf("%ld\n", mini);
}
