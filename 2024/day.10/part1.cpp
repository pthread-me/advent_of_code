#include <algorithm>
#include <iostream>
#include <fstream>
#include <optional>
#include <utility>
#include <vector>
#include <string>

using std::optional;
using std::vector;
using std::pair;

optional<vector<pair<int, int>>> merge_options(
		optional<vector<pair<int, int>>> up,optional<vector<pair<int, int>>> down,
		optional<vector<pair<int, int>>> left, optional<vector<pair<int, int>>> right){

	vector<pair<int,int>> res;
	if(up.has_value()){
		res.insert(res.begin(), up->begin(), up->end());
	}
	if(down.has_value()){
		res.insert(res.begin(), down->begin(), down->end());
	}
	if(left.has_value()){
		res.insert(res.begin(), left->begin(), left->end());
	}if(right.has_value()){
		res.insert(res.begin(), right->begin(), right->end());

	}

	return res;
}


optional<vector<pair<int, int>>> 
find_ends( vector<vector<int>> const &map, pair<int, int> pos, int rows, int columns){
	using namespace std;

	if(map[pos.first][pos.second] == 9){
		return vector({pos});
	}

	optional<vector<pair<int, int>>> up; 
	optional<vector<pair<int, int>>> down; 
	optional<vector<pair<int, int>>> left; 
	optional<vector<pair<int, int>>> right; 
	
	if(pos.first -1 >=0 && map[pos.first][pos.second] +1 == map[pos.first-1][pos.second] ){
		up = find_ends(map, pair(pos.first-1, pos.second), rows, columns);	
	}
	if(pos.first +1 < rows && map[pos.first][pos.second] +1 == map[pos.first+1][pos.second] ){
		down = find_ends(map, pair(pos.first+1, pos.second), rows, columns);	
	}
	if(pos.second -1 >=0 && map[pos.first][pos.second] +1 == map[pos.first][pos.second-1] ){
		left = find_ends(map, pair(pos.first, pos.second-1), rows, columns);	
	}
	if(pos.second < columns && map[pos.first][pos.second] +1 == map[pos.first][pos.second+1] ){
		right = find_ends(map, pair(pos.first, pos.second+1), rows, columns);	
	}
	return merge_options(up, down, left, right);
}


int main(){
	using namespace std; 

	fstream input("input.txt");
	string line;
	vector<vector<int>> map;
	vector<pair<int, int>> starting_pos;	

	for(int i=0; getline(input, line); i++){
		vector<int> int_vec(line.size());
		
		for(int j=0; j<int_vec.size(); j++){
			int_vec[j] = line[j] - '0';
			if(int_vec[j] == 0){
				starting_pos.push_back(pair(i,j));
			}
		}

		map.push_back(int_vec);
	}
	
	int rows = map.size();
	int columns = map[0].size();
	int sum =0;


	for(auto start: starting_pos){
		auto ends = find_ends(map, start, rows, columns).value_or(vector<pair<int,int>>({}));
	
		//removing dupes
		sort(ends.begin(), ends.end());
		auto new_end = unique(ends.begin(), ends.end());
		ends.erase(new_end, ends.end());		

		sum+= ends.size();
	}

	cout << sum << endl;
	
}
