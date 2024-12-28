#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <tokenizer.hpp>

bool valid(std::pair<int, int> p, int rows, int columns){
	return p.first>=0 && p.second >=0 && p.first<rows && p.second<columns;
}

bool operator< (const std::pair<int, int>& a, const std::pair<int, int>& b){
	return a.first<b.first;	
}

bool operator== (const std::pair<int, int>& a, const std::pair<int, int>& b){
	return a.first==b.first && a.second==b.second;	
}

std::pair<int,int> operator+(const std::pair<int, int>& a, const std::pair<int, int>& b ){
	return std::pair(a.first + b.first, a.second + b.second);
}

std::pair<int,int> operator-(const std::pair<int, int>& a, const std::pair<int, int>& b ){
	return std::pair(a.first - b.first, a.second - b.second);
}

int main(){
	using namespace std;
	
	fstream input("input.txt");
	string line;
	unordered_map<char, vector<pair<int,int>>> map;
	vector<pair<int, int>> antenodes;

	int rows=0;
	int columns=0;

	for(int i=0; getline(input, line); i++){
		if(i==0) columns = line.size();
		rows++;

		for(int j=0; j<line.size(); j++){
			if(line.at(j) != '.'){
			map[line.at(j)].push_back(pair(i, j));	
			}	
		}
	}



	for(auto row: map){
		for(auto iter=row.second.begin(); iter<row.second.end()-1; iter++){
			for(auto iter2 = iter+1; iter2<row.second.end(); iter2++){
				
				auto diff = *iter2 - *iter;
				auto node_1 = *iter - diff;	
				auto node_2 = *iter2 + diff;
			
				if(valid(node_1, rows,  columns)) antenodes.push_back(node_1);
				if(valid(node_2, rows,  columns)) antenodes.push_back(node_2);
			

			}		
	
		}	
	}

	sort(antenodes.begin(), antenodes.end());
	auto new_end = unique(antenodes.begin(), antenodes.end());	
	antenodes.erase(new_end, antenodes.end());

	cout << antenodes.size() << endl;	
}
