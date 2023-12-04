#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define base 10
#define NUMBER_OF_CARDS 202
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
	
	int card_number = 0;
	int card_value = 0;
	int card_multiplier[] = {[0 ... NUMBER_OF_CARDS-1] = 1};	

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
				card_value++;
			}
			token = strtok(NULL, &delim);
		}


		for(int i=1; i<=card_value; i++){
			card_multiplier[i+card_number] += card_multiplier[card_number];
		}

		//resetting hash table and counter variables
		for(int i=0; i<10; i++){
			hash_table[winning_numbers[i]] = -1;
		}
		card_value =0;
		winning_index =0;
		card_number++;
	}

	for(int i=0; i<NUMBER_OF_CARDS; i++){
		sum+= card_multiplier[i];
	}

	printf("%d\n", sum);

}
