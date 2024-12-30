#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> directions = {
	std::pair(-1,-1),
	std::pair(-1,0),
	std::pair(-1,1),
	std::pair(0,-1),
	std::pair(0,1),
	std::pair(1,-1),
	std::pair(1,0),
	std::pair(1,1),
};

enum Terminal{
	$=0,
	S=1,
	A=2,
	M=3,
	X=4,
};

char tochar(Terminal t){
	switch (t) {
		case X: return 'X';
		case M: return 'M';
		case A: return 'A';
		case S: return 'S';
		default: return '\0';
	}
}




size_t spider(const std::shared_ptr<std::vector<std::string>> & matrix, int i, int j){
	using namespace std;
	size_t sum =0;

	for(pair<int, int> p : directions){
		Terminal t = X;
		int p_i = i;
		int p_j = j;

		for(int len=0; len<4;len++){
			if(! (p_i>=0 && p_i < matrix->size() && p_j >= 0 && p_j < matrix->at(i).size())){
				break;
			}
			
			if(matrix->at(p_i).at(p_j) == tochar(t)){
				t = static_cast<Terminal>(t-1);
				p_i = p_i + p.first;
				p_j = p_j + p.second;
			}else {
				break;
			}
		}

		if(t == $) sum++;
	}

	return sum;
}

int main(){
	using namespace std;

	fstream input("input.txt");
	string line;
	size_t total =0;

	auto matrix = make_shared<vector<string>>();
	while(getline(input, line)){
		matrix->push_back(line);		
	}

	for(size_t i=0; i< matrix->size(); i++){
		for(size_t j=0; j<matrix->at(i).size(); j++){
			if(matrix->at(i).at(j) == tochar(X)){
				total += spider(matrix, i, j);
			}	
		}
	}

	cout << total;
}


