#include <iostream>
#include <fstream>
#include <string>
#include <tokenizer.hpp>


int main(){
	using namespace std;

	ifstream input("part1.input");
	string line;

	size_t sum=0;

	while(getline(input, line)){
		auto tokens = tokenize(line, ",");
		sum+= stoi(tokens.at(0)) * stoi(tokens.at(1));
	}

	cout << sum;

	








}
