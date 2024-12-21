#include <iostream>
#include <fstream>
#include <string>
#include <tokenizer.hpp>


int main(){
	using namespace std;

	ifstream input("part2.input");
	string line;

	size_t sum=0;
	bool mul = true;

	while(getline(input, line)){
		if(!line.compare("do()")){
			mul = true;
		}else if(!line.compare("don't()")){
			mul = false;
		}else if (mul){
			auto tokens = tokenize(line, ",");
			sum += stoi(tokens.at(0)) * stoi(tokens.at(1));
		}
	}

	cout << sum;

	








}
