#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define LINES 140

int sum =0;

long get_number(int i, int j, char** matrix, int line_length){
	char* buffer = calloc(10, sizeof(char));
	//setting the digit to the middle of the buffer to allow for wiggle space
	buffer[5] = matrix[i][j];
	int start =5;
	int end = 5;
	for(int left=1; j-left>-1; left++){
		if(isdigit(matrix[i][j-left])>0){
			buffer[5-left] = matrix[i][j-left];
			start--;
		}else{
			break;
		}
	}

	for(int right=1; j+right<line_length; right++){
		if(isdigit(matrix[i][j+right])>0){
			buffer[5+right] = matrix[i][j+right];
			end++;
		}else{
			break;
		}
	}

	char* e = &buffer[end];	
	long r = strtol(&buffer[start], &e, 10);
	
	return r;  
}

bool add_uniques(long cur, long* array, int index){
	for(int i=0; i<6; i++){
		if(array[i] == cur){
			return false;
		}
	}
	array[index] = cur;
	return true;
}

void handle_astrik(int line_index, int char_index, char** matrix, int line_length){
	int array_counter=0;
	long* uniques = calloc(6, sizeof(long));
	long current=0;

	//check top row
	if(line_index-1 >-1){
		if(char_index-1>-1 && isdigit(matrix[line_index-1][char_index-1])){
			current = get_number(line_index-1, char_index-1, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}

		if(char_index+1<line_length && isdigit(matrix[line_index-1][char_index+1])){
			current = get_number(line_index-1, char_index+1, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}

		if(isdigit(matrix[line_index-1][char_index])){
			current = get_number(line_index-1, char_index, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}
	}

	//checks bottom row
	if(line_index+1 <LINES){
		if(char_index-1>-1 && isdigit(matrix[line_index+1][char_index-1])){
			current = get_number(line_index+1, char_index-1, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}

		if(char_index+1<line_length && isdigit(matrix[line_index+1][char_index+1])){
			current = get_number(line_index+1, char_index+1, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}

		if(isdigit(matrix[line_index+1][char_index])){
			current = get_number(line_index+1, char_index, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}
	}

	//checks same row
	if(char_index-1>-1 && isdigit(matrix[line_index][char_index-1])){
		  	current = get_number(line_index, char_index-1, matrix, line_length);
			if(add_uniques(current, uniques, array_counter)){
				array_counter++;
			}			
		}

	if(char_index+1<line_length && isdigit(matrix[line_index][char_index+1])){
		current = get_number(line_index, char_index+1, matrix, line_length);
		if(add_uniques(current, uniques, array_counter)){
			array_counter++;
		}			
	}


	if(array_counter == 2){
		sum += uniques[0]*uniques[1];
	}
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
/*
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


*/
	//part2, we now make a second sweep and find multiplications (subtracting the values which will be multipled ofc)
	for(int i=0; i<LINES; i++){
		for(int j=0; j<chars_read; j++){
			if(matrix[i][j] == '*'){
				handle_astrik(i, j, matrix, chars_read);
			}

		}
	}
	
	printf("%d\n", sum);
}
