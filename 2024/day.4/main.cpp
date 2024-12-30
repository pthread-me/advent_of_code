#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


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




bool spider(const std::shared_ptr<std::vector<std::string>> & matrix, int i, int j){
	using namespace std;

	if(!(i-1>=0 && i+1 < matrix->size() && j-1 >= 0 && j+1 < matrix->at(i).size())) return false;
	
	pair TL = pair(i-1, j-1);
	pair TR = pair(i-1, j+1);
	pair BL = pair(i+1, j-1);
	pair BR = pair(i+1, j+1);

	bool TLBR = (matrix->at(TL.first).at(TL.second) == tochar(M) &&  matrix->at(BR.first).at(BR.second) == tochar(S))
		|| (matrix->at(TL.first).at(TL.second) == tochar(S) &&  matrix->at(BR.first).at(BR.second) == tochar(M));


	bool TRBL = (matrix->at(TR.first).at(TR.second) == tochar(M) &&  matrix->at(BL.first).at(BL.second) == tochar(S))
		|| (matrix->at(TR.first).at(TR.second) == tochar(S) &&  matrix->at(BL.first).at(BL.second) == tochar(M));
		

	return TRBL && TLBR;
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
			if(matrix->at(i).at(j) == tochar(A)){
				total += spider(matrix, i, j);
			}	
		}
	}

	cout << total;
}


