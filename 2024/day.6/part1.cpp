#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

//preprocessed data
#define COLUMNS  131
#define ROWS  130

//end of preprocessed data

typedef struct Cursor{
	int i;
	int j;
	char c;
}Cursor;

std::vector<std::vector<int>> rows(ROWS);
std::vector<std::vector<int>> columns(COLUMNS);
std::vector<std::vector<std::pair<int, int>>> visited;
Cursor cursor;

void read_input(){
	using namespace std;
	
	fstream input("input.txt");
	string line; 

	for(int i=0; getline(input, line); i++){
		for(int j=0; j<line.size(); j++){
			if(line.at(j) == '#'){
				columns.at(j).push_back(i);
				rows.at(i).push_back(j);
			}else if(line.at(j) == 'v' || line.at(j) == '>' || line.at(j) == '<' || line.at(j) == '^'){
				cursor.i = i;
				cursor.j = j;
				cursor.c = line.at((j));
			}
		}
	}
	input.close();
}

char rotate(char c){
	switch (c) {
		case '^':
			return '>';
		case '>':
			return 'v';
		case 'v':
			return '<';
		default:
			return '^';
	}	
}

std::pair<int, int> find_barrier(){
	using namespace  std;
	
	vector<int>::iterator end;
	char c = cursor.c;

	if(c == '>'){
		for(int pos =0; pos < rows.at(cursor.i).size(); pos++){
			if(cursor.j < rows.at(cursor.i).at(pos)){
				return pair(cursor.i, rows.at(cursor.i).at(pos));
			}	
		}
		return pair(cursor.i, COLUMNS);
	}else if(c == '<'){
		for(int pos = rows.at(cursor.i).size()-1; pos>=0 ; pos--){
			if(cursor.j > rows.at(cursor.i).at(pos)){
				return pair(cursor.i, rows.at(cursor.i).at(pos));
			}	
		}
		return pair(cursor.i, -1);
	}else if(c == 'v'){
		for(int pos = 0; pos < columns.at(cursor.j).size(); pos++){
			if(cursor.i < columns.at(cursor.j).at(pos)){
				return pair(columns.at(cursor.j).at(pos), cursor.j);
			}
		}
		return pair(ROWS, cursor.j);
	}else{
		for(int pos = columns.at(cursor.j).size()-1; pos>= 0; pos--){
			if(cursor.i > columns.at(cursor.j).at(pos)){
				return pair(columns.at(cursor.j).at(pos), cursor.j);
			}
		}
		return pair(-1, cursor.j);
	}
}

void add_visited(std::pair<int, int> barrier_pos){
	using namespace std;
	if(cursor.i == barrier_pos.first){
		if(cursor.j < barrier_pos.second){
			for(int j=cursor.j+1; j< barrier_pos.second; j++){
				visited.push_back({pair(cursor.i, j)});
			}
		}else{
			for(int j=cursor.j-1; j> barrier_pos.second; j--){
				visited.push_back({pair(cursor.i, j)});
			}
		}	
	}else{
		if(cursor.i < barrier_pos.first){
			for(int i=cursor.i+1; i< barrier_pos.first; i++){
				visited.push_back({pair(i, cursor.j)});
			}
		}else{
			for(int i=cursor.i-1; i> barrier_pos.first; i--){
				visited.push_back({pair(i, cursor.j)});
			}
		}
	}
}

int main(){
	using namespace std;
	read_input();

	pair<int, int> barrier_pos;
	visited.push_back({pair(cursor.i, cursor.j)});

	while(true){
		int diff =0;
		barrier_pos = find_barrier();
		
		add_visited(barrier_pos);

		//horizontal move
		if(barrier_pos.first == cursor.i){
			diff += (abs(barrier_pos.second - cursor.j) -1);
			if(barrier_pos.second > cursor.j){
				cursor.j += diff; 			
			}else{
				cursor.j -= diff;
			}
		//vertical move
		}else{
			diff += (abs(barrier_pos.first - cursor.i) -1);
			if(barrier_pos.first>cursor.i){
				cursor.i += diff;
			}else{
				cursor.i -= diff;
			}
		}
	
		cursor.c = rotate(cursor.c);
		if(barrier_pos.first == -1 || barrier_pos.first == ROWS || barrier_pos.second == -1 || barrier_pos.second == COLUMNS){
			break;
		}
	}
	sort(visited.begin(), visited.end());
	auto new_end = unique(visited.begin(), visited.end());
	visited.erase(new_end, visited.end());

	cout << visited.size() << endl;
}
