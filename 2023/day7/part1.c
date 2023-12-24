#include "../lib/main.h"
#include "../lib/linked_list.h"
#include "main.h"

const char* INPUT_FILE = "input";

int char_to_int(char a){

	if(isdigit(a)){
		return a - '0';
	}

	switch(a){
		case 'A':
			return A;
		case 'K':
			return K;
		case 'Q':
			return Q;
		case 'J':
			return J;
		case 'T':
			return T;
	}
	return -1;	

}

int compare(void* x, void* y){

	Card* a = (Card*)x;
	Card* b = (Card*)y;

	char* al = a->str;
	char* bl = b->str;

	if(a->type != b->type){
	//	printf("compare by type %s and %s\n, returned %d\n", al, bl, a->type - b->type);
		return (a->type - b->type);
	}

	for(int i=0; al[i]!='\0' && bl[i]!='\0'; i++){
		int ai = char_to_int(al[i]);
		int bi = char_to_int(bl[i]);

		if(ai != bi){
	//		printf("compare by char %s and %s\n, returned %d\n", al, bl, ai - bi);
			return ai - bi;
		}
	}
	return 0;
}

int get_type(int* array){
	bool five = false;
	bool four = false;
	bool three = false;
	int pairs = 0;
	
	for(int i=0; i<15; i++){
		switch(array[i]){
			case 5:
				five = true;
				break;
			case 4:
				four = true;
				break;
			case 3:
				three = true;
				break;
			case 2:
				pairs ++;
				break;
		}
	}

	if(five){
		return five_kind; 
	}else if(four){
		return four_kind;
	}else if(three && pairs==1){
		return full_house;
	}else if(three){
		return three_kind;
	}else if(pairs==2){
		return two_pair;
	}else if(pairs==1){
		return one_pair;
	}else{
		return high_card;
	}
}

void lhash(char* letters, int* array){
	
	for(int i=0; letters[i] != '\0'; i++){
		char curr = letters[i];
	
		if(isdigit(curr)){
			int index = curr - '0';
			array[index] ++;
		}
		
		switch(curr){
			case 'A':
				array[A] ++;
				break;
			case 'K':
				array[K] ++;
				break;
			case 'Q':
				array[Q] ++;
				break;
			case 'J':
				array[J] ++;
				break;
			case 'T':
				array[T] ++;
				break;
	
		}
	}
	
}

void print(void* v){
	Card* card = (Card*)v;
	printf("Card: %s\t%d\n", card->str, card->value);
}
int main(){
	
	FILE* file = fopen(INPUT_FILE, "r");
	size_t line_size =0;
	int chars_read;
	char* line;
	int total_lines=0;
	int hash_table[] = {[0 ... 14] = 0}; 

	//finding the total number of lines to use when initializing the array
	while(	(chars_read = getline(&line, &line_size, file)) >0	){

		total_lines++;
	}
	printf("%d\n", total_lines);
	fclose(file);

	List* ranks = list_create();

	file = fopen(INPUT_FILE, "r");
	while(	(chars_read = getline(&line, &line_size, file)) >0	){
		
		//removing trailing \n
		line[chars_read -1] = '\0';		

		char* letters = strtok(line, " ");
		char* numbers = strtok(NULL, " ");
	
		lhash(letters, hash_table);
		int type = get_type(hash_table);

		//create Card
		Card* card = calloc(1, sizeof(Card));
		card->str = calloc(1, sizeof(char*));
		strcpy(card->str, letters);
		card->value = strtol(numbers, NULL, 10);
		card->type = type;

		//clear hash table
		for(int i=0; i<15; i++){
			hash_table[i] = 0;
		}
		list_insertion_sort(ranks, compare, card);
	}
	printf("%d\n", ranks->length);
	print_list(ranks, print);

	void* cur = NULL;

	int total =0;
	for(int i=1; (cur = iterator(ranks)) != NULL; i++){
		Card* cur_card = (Card*) cur;
		total += i*cur_card->value; 
	}
	printf("total is %d\n", total);
}
