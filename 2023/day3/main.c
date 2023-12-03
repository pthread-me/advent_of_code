#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LINES 140

int sum =0;

bool is_symbol(char c){
	return (isdigit(c)==0 && c!='.');
}

bool check_surroundings(int line_number, int first, int last, char** matrix, int line_length){
	for(int i= first; i<last+1; i++){
		
		//checks line above
		if(line_number-1 > -1){
			if(i-1 > -1 && is_symbol(matrix[line_number-1][i-1])){
				return true;
			}
			if(i+1 < line_length && is_symbol(matrix[line_number-1][i+1])){
				return true;
			}
			if(is_symbol(matrix[line_number-1][i])){
				return true;
			}
		}

		//check line bellow
		if(line_number+1 < LINES){
			if(i-1 > -1 && is_symbol(matrix[line_number+1][i-1])){
				return true;
			}
			if(i+1 < line_length && is_symbol(matrix[line_number+1][i+1])){
				return true;
			}
			if(is_symbol(matrix[line_number+1][i])){
				return true;
			}
		}

		//check same line
		if(i-1 > -1 && is_symbol(matrix[line_number][i-1])){
			return true;
		}
		if(i+1 < line_length && is_symbol(matrix[line_number][i+1])){
			return true;
		}
		if(is_symbol(matrix[line_number][i])){
			return true;
		}
	}
	return false;
}


int main(){

	FILE* input = fopen("./input", "r");

	size_t getline_size = 0;
	int chars_read;
	char** matrix = calloc(LINES, sizeof(char*));
	
	//indicies
	int first =-1;
	int last =-1;
	long valid_number=0;

	//reading in the matrix
	for(int i=0; i<LINES; i++){
		chars_read = getline(&matrix[i], &getline_size, input);
		if(chars_read<1){
			fprintf(stderr, "ruh oh");
			exit(EXIT_FAILURE);
		}

		//getline reads \n so to offset this we replace it with a . which is considered NULL in this use case
		matrix[i][chars_read-1] = '.';
	}

	for(int i=0; i<LINES; i++){
		for(int j=0; j<chars_read; j++){
			if(isdigit(matrix[i][j])>0 && first<0){
				first = j;
				last = j;
				continue; 
			}else if(isdigit(matrix[i][j])>0){
				last = j;
				continue;
			}else if(first == -1){
				continue;
			}

			if(check_surroundings(i, first, last, matrix, chars_read)){
					char* buffer = calloc(20, sizeof(char));
					for(int start=0; start+first<=last; start++){
						buffer[start] = matrix[i][start+first];
					}
					sum += strtol(buffer, NULL, 10);
			}
			first = -1;
			last = -1; 
		}
	}

	printf("%d\n", sum);
}
