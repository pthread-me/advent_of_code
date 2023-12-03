//
// Created by anasn on 2023-12-01.
//
#define _GNU_SOURCE
#include "main.h"
#include "stdlib.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
int main(int argc, char** argv){

    char* line;
    FILE* input = fopen("./input.txt", "r");
	FILE* output = fopen("output.txt", "w");

    size_t line_size = 0;
    int chars_read;
    char first;
	char last;
	char* first_array;
	char* last_array;
	bool first_filled = false;
	bool last_filled = false;
	int sum =0;

	while( (chars_read = getline(&line, &line_size, input) -1) >0){
		for(int i=0; i<chars_read; i++){

			//checks for ints
			if(!first_filled && isdigit(line[i])>0){
				first = line[i];
				first_filled = true;
			}

			if(!last_filled && isdigit(line[chars_read-i-1])>0){
				last = line[chars_read-i-1];
				last_filled = true;
			}


			if(i+4 < chars_read  && !first_filled){
				first_array = calloc(5, sizeof(char));
				for(int j=0; j<5; j++){
					first_array[j] = line[i+j];
				}

				if(strcmp(first_array, "eight") == 0){
					first = '8';
					first_filled = true;
				}else if(strcmp(first_array, "three") == 0){
					first = '3';
					first_filled = true;
				}else if(strcmp(first_array, "seven")==0){
					first = '7';
					first_filled = true;
				}
				free(first_array);
			
			}if(i+3 <chars_read && !first_filled){
				first_array = calloc(4, sizeof(char));
				for(int j=0; j<4; j++){
					first_array[j] = line[i+j];
				}
				
				if(strcmp(first_array, "nine")==0){
					first = '9';
					first_filled = true;
				}else if(strcmp(first_array, "five")==0){
					first = '5';
					first_filled = true;
				}else if(strcmp(first_array, "four")==0){
					first = '4';
					first_filled = true;
				}
				free(first_array);

			}if(i+2 <chars_read  && !first_filled){
				first_array = calloc(3, sizeof(char));
				for(int j=0; j<3; j++){
					first_array[j] = line[i+j];
				}
				
				if(strcmp(first_array, "one")==0){
					first = '1';
					first_filled = true;
				}else if(strcmp(first_array, "two")==0){
					first = '2';
					first_filled = true;
				}else if(strcmp(first_array, "six")==0){
					first = '6';
					first_filled = true;
				}
				free(first_array);
			}



			if(chars_read - i - 4 > -1 && !last_filled){
				last_array = calloc(5, sizeof (char));
				for(int j=0; j<5; j++){
					last_array[4-j] = line[chars_read-i-j];
				}

				if(strcmp(last_array, "eight") == 0){
					last = '8';
					last_filled = true;
				}else if(strcmp(last_array, "three") == 0){
					last = '3';
					last_filled = true;
				}else if(strcmp(last_array, "seven")==0){
					last = '7';
					last_filled = true;
				}
			}if(chars_read - i -3 > -1 && !last_filled){
				last_array = calloc(4, sizeof (char));
				for(int j=0; j<4; j++){
					last_array[3-j] = line[chars_read-i-j];
				}

				if(strcmp(last_array, "nine") == 0){
					last = '9';
					last_filled = true;
				}else if(strcmp(last_array, "four") == 0){
					last = '4';
					last_filled = true;
				}else if(strcmp(last_array, "five")==0){
					last ='5';
					last_filled = true;
				}
			}if(chars_read -i- 2 > -1 && !last_filled){
				last_array = calloc(3, sizeof (char));
				for(int j=0; j<3; j++){
					last_array[2-j] = line[chars_read-i-j];
				}

				if(strcmp(last_array, "one") == 0){
					last = '1';
					last_filled = true;
				}else if(strcmp(last_array, "two") == 0){
					last = '2';
					last_filled = true;
				}else if(strcmp(last_array, "six")==0){
					last ='6';
					last_filled = true;
				}
			}
			
			

			if(first_filled && last_filled){

				//converting chars to int, we only have 2 chars so this is hard coded
				sum += (first -'0')*10 + (last - '0');
				break;
			}
		}
		
		first_filled = false;
		last_filled = false;	
	}	


	fprintf(output, "%d\n", sum);		
}
