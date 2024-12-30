#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <unordered_map>
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


	/*
	 * Part1 logic
	int sum = 0;
	for(int i=0; i<column1->size(); i++){
		sum+= abs(column1->at(i) - column2->at(i));
	}
	*/
	
	int sum = 0;
	int last_checked = -1;

	unordered_map<int, int>	umap;

	for(size_t i=0; i<column1->size(); i++){	
		int value = column1->at(i);

		if(value <= last_checked){
			sum += umap.at(value);
			continue;
		}
		
		//look at docs, this returns an iterator pair (first, second)
		//first: points to element in vector with value >= searched value
		//second: points to an element in vector with value > searched value
		auto iter_pair = equal_range(column2->begin(), column2->end(), value );
		
		int range = distance(iter_pair.first, iter_pair.second);
		sum += (range*value);
		umap[value] = range*value;

		//removing the checked elements from col2 as the value will be in umap
		column2->erase(iter_pair.first, iter_pair.second);
			
	}

	cout << sum << flush;
}
