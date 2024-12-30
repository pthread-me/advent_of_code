#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <tokenizer.hpp>
#include <unordered_map>
#include <memory>
#include <vector>

std::unordered_map<int, std::vector<int>> map; 

std::unordered_map<int, std::vector<int>> get_rules(){
	using namespace  std;

	fstream input("rules.txt");
	string line;
	auto map = unordered_map<int, vector<int>>();

	while(getline(input, line)){
		auto tokens = tokenize(line, "|");
		int key = stoi(tokens.at(0));
		int val = stoi(tokens.at(1));

		if(map.count(key)){
			map.at(key).push_back(val);
		}else{
			map.insert({key, vector<int>({val})});
		}	
	}
	
	input.close();
	return map;
}


bool check(int key, const std::vector<int>& row){
	using namespace std;
	
	auto rules = map.find(row.at(key))->second;

	for(int i=key+1; i<row.size(); i++){
		if(find(rules.begin(), rules.end(), row.at(i)) != rules.end()){
			return false;
		}
	}

	return true;
}

bool cmp(int a, int b){
	using namespace std;

	auto a_rules =map.count(a)>0? map.find(a)->second : vector<int>(0);
	auto b_rules = map.count(b)>0? map.find(b)->second: vector<int>(0);
	
	if(!a_rules.empty() && find(a_rules.begin(), a_rules.end(), b) != a_rules.end()){
			return true;
	}else if(!b_rules.empty() && find(b_rules.begin(), b_rules.end(), a) != b_rules.end()){
			return false;
	}

	return a<b;
}
int sum(std::vector<std::vector<int>> ordered){
	int sum =0;

	for(auto row: ordered){
		int mid = row.size()/2;
		sum += row.at(mid);
	}

	return sum;
}



int main(){
	using namespace std;
	
	map = get_rules();
	vector<vector<int>> matrix;
	vector<vector<int>> ordered;
	
	fstream input("data.txt");
	string line;

	while(getline(input, line)){
		auto tokens = tokenize(line, ",");
		vector<int> row(tokens.size());

		transform(tokens.begin(), tokens.end(), row.begin(), [](string token){
			return stoi(token);
		});
		
		reverse(row.begin(), row.end());
		matrix.push_back(row);
	}


	for(auto row: matrix){
		bool valid = true;	
		for(int i=0; i<row.size(); i++){
			if(map.count(row.at(i))){
				valid = check(i, row);
				if(!valid) break;
			}
		}

		if(!valid) ordered.push_back(row);
	}


	for(int i=0; i<ordered.size(); i++){
		sort(ordered.at(i).begin(), ordered.at(i).end(), cmp);
	}

	for(auto row: ordered){
		for(int num : row){
			cout << num << " ";
		}	
		cout << endl;
	}

	cout << "Sum is: " << sum(ordered) << endl;
}
