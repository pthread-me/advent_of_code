#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define base 10
const char delim = ' ';
int sum =0;
int main(){
	
	FILE* input = fopen("./input", "r");
	
	size_t getline_size = 0;
	char* line;
	int chars_read;
	char* token;
	long current_number;

	long hash_table[] = {[0 ... 99] = -1};
	long winning_numbers[] = {[0 ... 9] = 0};
	int winning_index =0;

	bool at_least_one = false;
	int card_value=0;

	while( (chars_read = getline(&line, &getline_size, input))>0){


		//skipping to firts number 
		strtok(line, &delim);
		strtok(NULL, &delim);		
		strtok(NULL, &delim);		
		token = strtok(NULL, &delim);

		//adding winning numbers to a hash table		
		while(strcmp(token, "|") !=0){
			current_number = strtol(token, NULL, base);
			winning_numbers[winning_index] = current_number;
			winning_index++;
			hash_table[current_number] = current_number;		
			token = strtok(NULL, &delim);
		}
		
		//looking up hash table
		token = strtok(NULL, &delim);
		while(token != NULL){
			current_number = strtol(token, NULL, base);
			
			if(hash_table[current_number]==current_number){
				if(!at_least_one){
					card_value = 1;
					at_least_one = true;
				}else{
					card_value = card_value<<1;
				}
			}
			token = strtok(NULL, &delim);
		}


		//resetting hash table and counter variables
		for(int i=0; i<10; i++){
			hash_table[winning_numbers[i]] = -1;
		}
		sum += card_value;
		card_value =0;
		at_least_one = false;
		winning_index =0;
	}

	printf("%d\n", sum);
}
