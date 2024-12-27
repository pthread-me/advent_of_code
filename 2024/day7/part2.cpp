#include <iostream>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <string>
#include <tokenizer.hpp>
#include <vector>
#include <cmath>

bool check(long target, long sum, size_t i, const std::vector<long>& vec){
	using namespace std;

	if(sum == target){
		return true;
	}else if(sum > target || i >= vec.size()){
		return false;
	}

	long next = vec.at(i);
	long sum_len = log10(sum) +1;
	long next_len = log10(next) +1;

	bool concat = sum_len+next_len <= log10(target) +1;

	return check(target, sum * vec.at(i), i+1,  vec) || 
		check(target, sum + vec.at(i), i+1, vec) ||
		(concat && check(target, (sum* pow(10,next_len)) + next, i+1, vec));
}

int main(){
	using namespace std;
	fstream input("input.txt");
	string line;
	vector<vector<long>> expressions;

	while(getline(input, line)){
		auto tokens = tokenize(line, " ");
		tokens.at(0) = tokens.at(0).substr(0, tokens.at(0).size()-1);
	
		vector<long> expression(tokens.size());

		std::transform(tokens.cbegin(), tokens.cend(), expression.begin(), [](string str){
				return stol(str);
		});

		expressions.push_back(expression);
	}	

	long sum =0;
	for(auto expression : expressions){
		sum += check(expression.at(0), expression.at(1), 2, expression)? expression.at(0): 0;
	}
	cout << sum << flush;
}
