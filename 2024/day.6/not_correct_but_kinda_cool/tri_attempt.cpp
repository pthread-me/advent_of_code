#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

//preprocessed data
#define COLUMNS   10// 131
#define ROWS    10//130
#define INPUT "test.txt"

//end of preprocessed data

typedef struct Cursor{
	int i;
	int j;
	char c;
}Cursor;

typedef struct Triplet{
	std::pair<int, int> f;
	std::pair<int, int> s;
	std::pair<int, int> t;

	friend bool operator== (Triplet a, Triplet b){
		return a.f == b.f && a.s == b.s && a.t == b.t;
	}
	
	friend bool operator< (Triplet a, Triplet b){
		return a.f < b.f;
	}
} Triplet;

std::vector<std::vector<int>> rows(ROWS);
std::vector<std::vector<int>> columns(COLUMNS);
std::vector<std::pair<int, int>> barrier_hit;
std::vector<Triplet> triples;
Cursor cursor;

void read_input(){
	using namespace std;
	
	fstream input(INPUT);
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
	
/**
 *	first, second and third barriers we hit.	
 */
std::pair<int, int> find_cycle(std::pair<int, int> f, std::pair<int, int> s, std::pair<int, int> t){
	using namespace std;
	pair<int, int> barrier;
	barrier.first = -1;
	barrier.second = -1;

	if(f.first +1 == s.first && s.second -1 == t.second){
		barrier.first = t.first -1;
		barrier.second = f.second -1;
	}else if(f.second -1 == s.second && s.first -1 == t.first){
		barrier.first = f.first -1;
		barrier.second = t.second +1;
	}else if(f.first -1 == s.first && s.second +1 == t.second){
		barrier.first = t.first +1;
		barrier.second = f.second +1;
	}else if(f.second +1 == s.second && s.first +1 == t.first){
		barrier.first = f.first +1;
		barrier.second = t.second -1;
	}

	return barrier;
}

bool cycle_validity(std::pair<int, int> barrier, std::pair<int, int> f, std::pair<int, int> t){
	using namespace std;
	if(barrier.first == -1 || barrier.first == ROWS || barrier.second == -1 || barrier.second == COLUMNS){
		return false;
	}
	
	if(barrier.second +1 == f.second){
		for(int i=barrier.first; i> f.first; i--){
			if(find(columns.at(f.second).begin(), columns.at(f.second).end(), i) != columns.at(f.second).end()){
				return false;
			}
		}

		for(int i=barrier.second+1; i< t.second; i++){
			if(find(rows.at(barrier.first).begin(), rows.at(barrier.first).end(), i) != rows.at(barrier.first).end()){
				return false;
			}
		}
	}else if(barrier.first +1 == f.first){
		for(int i= barrier.second; i<f.second; i++){
			if(find(rows.at(f.first).begin(), rows.at(f.first).end(), i) != rows.at(f.first).end()){
				return false;
			}
		}

		for(int i=barrier.first+1; i< t.first; i++){
			if(find(columns.at(barrier.second).begin(), columns.at(barrier.second).end(), i) != 
					columns.at(barrier.second).end()){
				return false;
			}
		}

	}else if(barrier.second-1 == f.second){
		for(int i=barrier.first; i< f.first; i++){
			if(find(rows.at(f.second).begin(), rows.at(f.second).end(), i) != rows.at(f.second).end()){
				return false;
			}
		}

		for(int i=barrier.second-1; i>t.second; i--){
			if(find(rows.at(barrier.second).begin(), rows.at(barrier.second).end(), i) != rows.at(barrier.second).end()){
				return false;
			}
		}
	}else if(barrier.first-1 == f.first){
		for(int i=barrier.second; i> f.second; i--){
			if(find(rows.at(f.first).begin(), rows.at(f.first).end(), i) != rows.at(f.first).end()){
				return false;
			}
		}

		for(int i=barrier.first-1; i>t.first; i--){
			if(find(columns.at(barrier.second).begin(), columns.at(barrier.second).end(), i) != columns.at(barrier.second).end()){
				return false;
			}
		}
	}

	return true;
}


int main(){
	using namespace std;
	read_input();

	pair<int, int> barrier_pos;

	while(true){
		int diff =0;
		barrier_pos = find_barrier();
		barrier_hit.push_back(barrier_pos);		

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

	pair<int, int> barrier;
	int valid_cycles =0;

	for(int i=0; i< barrier_hit.size()-2; i++){
		Triplet tri;
		tri.f = barrier_hit.at(i);
		tri.s = barrier_hit.at(i+1);
		tri.t = barrier_hit.at(i+2);
		triples.push_back(tri);	
	}

	/*
	sort(triples.begin(), triples.end());
	auto new_end = unique(triples.begin(), triples.end());
	triples.erase(new_end, triples.end());
*/

	/*
	for(int i=0; i< barrier_hit.size()-3; i++){
		barrier = find_cycle(barrier_hit.at(i), barrier_hit.at(i+1), barrier_hit.at(i+2));	
		valid_cycles += cycle_validity(barrier, barrier_hit.at(i));	
	}
	*/
	
	for(int i=0; i<triples.size(); i++){
		barrier = find_cycle(triples.at(i).f, triples.at(i).s, triples.at(i).t);
		valid_cycles += cycle_validity(barrier, triples.at(i).f, triples.at(i).t);	
	}
	

	cout << valid_cycles << endl;
}
