#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


const char delim = ' ';
const int base =10;
const int RED_MAX = 12;
const int BLUE_MAX = 14;
const int GREEN_MAX = 13;
int sum=0;
int red_max=0;
int blue_max=0;
int green_max=0;
int power_set =0;

typedef enum colors{
	RED,
	BLUE,
	GREEN
}Colors;


Colors get_color(char* raw_text){
	char color[5];

	for(int i=0; i<5; i++){
		color[i] = raw_text[i];

		if(strcmp(color, "red") == 0){
			return RED;
		}else if(strcmp(color, "blue") == 0){
			return BLUE;
		}else if(strcmp(color, "green") == 0){
			return GREEN;
		}
	}
}

bool check_count(long count, Colors color){
	switch(color){
		case RED:
			return count <= RED_MAX;
		case BLUE:
			return count <= BLUE_MAX;
		case GREEN:
			return count <= GREEN_MAX;
	}
}

void set_max(long count, Colors color){
	switch(color){
		case RED:
			red_max = red_max<count?count:red_max;
			break;
		case BLUE:
			blue_max = blue_max<count?count:blue_max;
			break;
		case GREEN:
			green_max = green_max<count?count:green_max;
			break;
	}
}

int main(){

	FILE* input = fopen("./input", "r");

	size_t getline_size =0;
	int chars_read;
	char* line;	
	char* token;

	long game_number;
	long cube_number;
	Colors cube_color;

	//used in the strtol func so that it reads the entire string, im pretty sure we can just replace this with a NULL
	char* end;


	bool valid_line = true;


	while ( (chars_read = getline(&line, &getline_size, input)) > 0){
		token = strtok(line, &delim);
		token = strtok(NULL, &delim);

		game_number = strtol(token, &end, base);		
		
		while((token = strtok(NULL, &delim)) != NULL){
			if(isdigit(token[0] == 0)){
				continue;
			}
			
			cube_number = strtol(token, &end, base);
			cube_color = get_color(strtok(NULL, &delim));			
		
			if(!check_count(cube_number, cube_color)){
				valid_line = false;
			}

			set_max(cube_number, cube_color);
		}

		if(valid_line){
			sum += game_number;
		}
		valid_line = true;

		power_set += red_max*blue_max*green_max;
		red_max =0;
		green_max =0;
		blue_max =0;
	}

	printf("sum of valid game ID's: %d\n", sum);
	printf("power of the set of cubes: %d\n", power_set);
}
