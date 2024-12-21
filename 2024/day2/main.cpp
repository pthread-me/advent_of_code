#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <tokenizer.hpp>
#include <algorithm>
#include <pthread.h>
#include <vector>

const size_t thread_num = 16;

int shared_count =0;
std::mutex mutex_lock;

typedef struct thread_data{
	std::shared_ptr<std::vector<std::vector<int>>> matrix;
	size_t start;
	size_t end;
}Pdata;

bool check_row(std::vector<int> row, bool increasing, bool chance){
	for(size_t i=0; i<row.size()-1; i++){
		if((increasing && row.at(i) >= row.at(i+1)) ||(!increasing && row.at(i) <= row.at(i+1)) || (abs(row.at(i) - row.at(i+1)) > 3)){
			
			if(!chance) {
				return false;
			}	
			std::vector<int> row1 = row, row2 =row;
			row1.erase(row1.begin() + i);
			row2.erase(row2.begin() + i+1);
			return check_row(row1, increasing,false) || check_row(row2, increasing, false);
		}
	}
	return true;
}

void* count_valid(void* args){
	using namespace std;

	Pdata* data = static_cast<Pdata*>(args);
	int valid_count =0;

	for(size_t i = data->start; i<= data->end; i++){
		vector<int> row = data->matrix->at(i);
		
		//check row direction
		bool increasing = false;
		for(size_t window =0; window<3; window++){
			if(row.at(window) < row.at(window+1) && row.at(window+1) < row.at(window+2)){
				increasing = true;
				break;
			}
		}

		if(check_row(row, increasing, true)) valid_count++;
	}
	

	mutex_lock.lock();
	shared_count += valid_count;
	mutex_lock.unlock();

	return nullptr;	
}


int main(){
	using namespace std;

	ifstream input("input.txt");
	string line;
	string delim(" ");

	shared_ptr<vector<vector<int>>> matrix = make_shared<vector<vector<int>>>(); 	

	while(getline(input, line)){

		auto tokens = tokenize(line, delim);	
		vector<int> row(tokens.size());

		// Just like map :: in haskell
		std::transform(tokens.begin(), tokens.end(), row.begin(), [](string token){
				return stoi(token);
		});
		matrix->push_back(row);
	}


	
	pthread_t threads[thread_num];
	Pdata data[thread_num];
	size_t matrix_size = matrix->size();
	size_t block_size = ceil(matrix->size() / 16.0);


	for(size_t i=0, j=0; i<matrix_size && j<thread_num; i+=block_size, j++){
		data[j].matrix = matrix;
		data[j].start = i;
		data[j].end = i+block_size-1;
			
		if(i+block_size-1 > matrix_size){
			data[j].end = matrix_size-1;
		}
	}

	for(int i=0; i<thread_num; i++){
		pthread_create(&threads[i], nullptr, count_valid, &data[i]);
	}

	
	for(int i=0; i<thread_num; i++){
		pthread_join(threads[i], nullptr);
	}

	/*
	Pdata data;
	data.matrix = matrix;
	data.start =0;
	data.end = matrix->size();
*/
	
	cout << shared_count << endl ;
}
