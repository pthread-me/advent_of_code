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


int shared_count =0;
int total_rows =0;
std::mutex mutex_lock;

typedef struct thread_data{
	std::shared_ptr<std::vector<std::vector<int>>> matrix;
	size_t start;
	size_t end;
}Pdata;

void* count_valid(void* args){
	using namespace std;

	Pdata* data = static_cast<Pdata*>(args);

	int valid_count =0;
	int rows_counted =0;

	for(size_t i = data->start; i<= data->end; i++){
		vector<int> row = data->matrix->at(i);
		bool valid_row = true;
		int size_violation = 0;
		int direction_change = 0;
		int direction =0; 

		for(size_t j =0; j<row.size()-1; j++){
			if(size_violation>1 || direction_change>2){
				valid_row = false;
				break;
			}
			if(row.at(j) - row.at(j+1) > abs(3)){
				size_violation ++;
			}

			if(row.at(j) < row.at(j+1) ){
				if(direction>0){
					continue;
				}else{
					direction_change++;
					direction++;
				}

			}else if(row.at(j) > row.at(j+1) ){
				if(direction< 0){
					continue;
				}else{
					direction_change++;
					direction--;
				}
			}else{
				direction_change++;
			}

		}

	if(valid_row) valid_count++;
		rows_counted++;	
	}	

	mutex_lock.lock();
	shared_count += valid_count;
	total_rows += rows_counted;
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

	pthread_t threads[16];
	Pdata data[16];
	size_t matrix_size = matrix->size();
	size_t block_size = ceil(matrix->size()/16.0);


	for(size_t i=0, j=0; i<matrix_size && j<16; i+=block_size+1, j++){
		data[j].matrix = matrix;
		data[j].start = i;
		data[j].end = i+block_size;
			
		if(i+block_size-1 > matrix_size){
			data[j].end = matrix_size-1;
		}
	}

	for(int i=0; i<16; i++){
		pthread_create(&threads[i], nullptr, count_valid, &data[i]);
	}

	
	for(int i=0; i<16; i++){
		pthread_join(threads[i], nullptr);
	}

	cout << shared_count << endl ;
	cout << total_rows << flush;
}
