#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <tokenizer.hpp>

int main(){
	using namespace std;
	
	unique_ptr<vector<int>> column1 = make_unique<vector<int>>();
	unique_ptr<vector<int>> column2 = make_unique<vector<int>>();
	ifstream input("input.txt");
	string line;
	string delim = string(" ");
	
	while(getline(input, line)){
		vector<string> tokens = tokenize(line, delim);
		column1->push_back(stoi(tokens[0]));
		column2->push_back(stoi(tokens[1]));
	}


	sort(column1->begin(), column1->end());
	sort(column2->begin(), column2->end());


	int sum = 0;
	for(size_t i=0; i<column1->size(); i++){
		sum+= abs(column1->at(i) - column2->at(i));
	}
	
	cout << sum << flush;
}
