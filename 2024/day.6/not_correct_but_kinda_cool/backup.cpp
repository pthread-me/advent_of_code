#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

//preprocessed data
#define COLUMNS  131
#define ROWS 130
#define INPUT "input.txt"
//end of preprocessed data

typedef struct Cursor{
	int i;
	int j;
	char c;

	friend bool operator== (Cursor a, Cursor b){
		return  (a.c == b.c);
	}
}Cursor;

std::vector<std::vector<int>> rows(ROWS);
std::vector<std::vector<int>> columns(COLUMNS);
std::vector<std::pair<int, int>> visited;

Cursor read_input(){
	using namespace std;
	
	fstream input(INPUT);
	string line; 
	Cursor cursor;

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
	return cursor;
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

void move_cusor(Cursor& cursor, std::pair<int, int> barrier){
	int moved_by =0;

	//horizontal move
	if(barrier.first == cursor.i){
		moved_by += (abs(barrier.second - cursor.j) -1);
		if(barrier.second > cursor.j){
			cursor.j += moved_by; 			
		}else{
			cursor.j -= moved_by;
		}
	//vertical move
	}else{
		moved_by += (abs(barrier.first - cursor.i) -1);
		if(barrier.first>cursor.i){
			cursor.i += moved_by;
		}else{
			cursor.i -= moved_by;
		}
	}	
}

std::pair<int, int> find_barrier(Cursor& cursor){
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

void add_visited(Cursor& cursor, std::pair<int, int> barrier_pos){
	using namespace std;
	if(cursor.i == barrier_pos.first){
		if(cursor.j < barrier_pos.second){
			for(int j=cursor.j+1; j< barrier_pos.second; j++){
				visited.push_back(pair(cursor.i, j));
			}
		}else{
			for(int j=cursor.j-1; j> barrier_pos.second; j--){
				visited.push_back(pair(cursor.i, j));
			}
		}	
	}else{
		if(cursor.i < barrier_pos.first){
			for(int i=cursor.i+1; i< barrier_pos.first; i++){
				visited.push_back(pair(i, cursor.j));
			}
		}else{
			for(int i=cursor.i-1; i> barrier_pos.first; i--){
				visited.push_back(pair(i, cursor.j));
			}
		}
	}
}

int main(){
	using namespace std;

	Cursor initial_cursor = read_input();
	Cursor cursor = initial_cursor;
	Cursor check_point_cursor = initial_cursor;

	pair<int, int> barrier_pos;
	pair<int, int> initial_bar = find_barrier(initial_cursor);
	int barrier_hit;

	visited.push_back(pair(cursor.i, cursor.j));

	//finding the path taken
	while(true){
		barrier_pos = find_barrier(cursor);

		add_visited(cursor, barrier_pos);
		move_cusor(cursor, barrier_pos);
		cursor.c = rotate(cursor.c);

		if(barrier_pos.first == -1 || barrier_pos.first == ROWS || barrier_pos.second == -1 || barrier_pos.second == COLUMNS){
			break;
		}
	}

	// removing dup
	sort(visited.begin(), visited.end());
	auto new_end = unique(visited.begin(), visited.end());
	visited.erase(new_end, visited.end());

	int loops = 0;

	for(int i=1; i<visited.size(); i++){

		if(i==19){
			cout << "hi";
		}

		pair<int, int> barrier = visited.at(i); 
		cursor = initial_cursor;
		barrier_hit =0;

		//adding new barrier
		rows.at(barrier.first).push_back(barrier.second);
		columns.at(barrier.second).push_back(barrier.first);

		sort(rows.at(barrier.first).begin(), rows.at(barrier.first).end());
		sort(columns.at(barrier.second).begin(), columns.at(barrier.second).end());
	

		for(int j=0; j<120; j++){
			barrier_pos = find_barrier(cursor);
			if(barrier_pos.first == barrier.first && barrier_pos.second == barrier.second){
				barrier_hit++;
			}

			move_cusor(cursor, barrier_pos);
			cursor.c = rotate(cursor.c);

			if(barrier_pos.first == -1 || barrier_pos.first == ROWS || barrier_pos.second == -1 || barrier_pos.second == COLUMNS){
				break;
			}

			if(j>0 && barrier_hit>10) {
				loops++;
				break;
			}
			if(i==19){
				cout << j << endl;
			}
		}
		cout << i << endl;
		rows.at(barrier.first).erase(find(rows.at(barrier.first).begin(), rows.at(barrier.first).end(), barrier.second));
		columns.at(barrier.second).erase(find(columns.at(barrier.second).begin(), columns.at(barrier.second).end(), barrier.first));
	}
	cout << visited.size() << endl;
	cout << "loop barriers: " << loops << endl;
}
