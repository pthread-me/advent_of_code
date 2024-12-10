#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "map.hpp"
using namespace std;

const bool 
compare(const Map& a,const Map& b){
	return a.src_start < b.src_start;
}


long
kinda_binary_search(long seed, vector<Map> map){
	long start = 0;
	long end = map.size() -1;
	long mid = map.size()/2;


	while (start < end){
		if(seed < map[mid].src_start){
			end = mid;
			mid = start + (end-start)/2;
		}else if (seed > map[mid].src_start + map[mid].range){
			start = mid;
			mid = start + (end-start)/2;
		}else{
			return map[mid].dest_start + seed - map[mid].src_start;
		}
	}

	return -1;

}


int
main(){
	
	vector<long> seeds;
	vector<vector<Map>> categories;

	ifstream input_file;
	input_file.open("input");
	
	string line;
	string token;

	if(getline(input_file, line)){
		istringstream line_stream(line);
		
		//ignoring the name of the mapping
		line_stream >> token;
		while(line_stream >> token){
			seeds.push_back(stol(token));
		}
	}

	//skipping the first empty line after seeds
	getline(input_file, line);
	vector<Map> map;	

	while(getline(input_file, line)){
		
		long src, dest, range;
		
		while(getline(input_file, line) && line != ""){
			istringstream line_stream(line);
			
			line_stream >> token;
			src = stol(token);	
			line_stream >> token;
			dest = stol(token);	
			line_stream >> token;
			range = stol(token);

			Map temp = Map(src, dest, range);
			map.push_back(temp);
		}

		std::sort(map.begin(), map.end(), compare);
		categories.push_back(map);
	}


	long sum =seeds[0];
	for(auto seed: seeds){
		long cur = seed;
		for(auto vec: categories){
			cur = kinda_binary_search(cur, vec);
		}

		sum = cur<sum? cur:sum;
	}

	cout << sum << endl;
	input_file.close();
	return 0;
}
