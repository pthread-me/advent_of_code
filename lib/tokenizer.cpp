#include <tokenizer.hpp>
#include <iostream>

std::vector<std::string> tokenize(std::string input, std::string delimeter){
	using namespace std;

	if(input.empty() || delimeter.empty()){
		cerr << "Error: Your strings are empty dumbass\nIn tokenize() in tokenizer.cpp" << endl;
		return vector<string>();
	}

	vector<string> tokens = vector<string>();
	char* str = &(input[0]);	
	char* delim = &(delimeter[0]);

	const char* token = strtok(str, delim);

	while(token != NULL){
		tokens.push_back(string(token));
		token = strtok(NULL, delim);
	}

	return tokens;
}
