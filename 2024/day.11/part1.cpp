#include <algorithm>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <iterator>
#include <tokenizer.hpp>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>


/*
 * I think i understand why we need a pair hash struct. 
 * Its to ensure that if a == b then h(a) == h(b). so the struct holds a "functor"
 * aka a mapping function from a -> h(a). this function needs to be the same 
 * for all a \in Problem set, to maintain the equality.
 */

struct PairHash{
	template <class T1, class T2> // we can have the template be <T1, T2> if its not a (size_t,size_t) pair. ex: pair(size_t, string)
	std::size_t operator()(std::pair<T1, T2> const &p) const {
		size_t first_hash = std::hash<T1>{}(p.first);
		size_t second_hash = std::hash<T2>{}(p.second);
	
		return first_hash ^ second_hash; // not a good way of combining hashes but should work
	}
};



size_t 
digits(size_t i){
	return std::log10(i) +1;
}

std::pair<size_t,size_t>
split_size_t(size_t i, size_t digits){
	size_t factor = trunc(pow(10, digits/2.0));

	size_t left = i/factor;
	size_t right = i - (left*factor);

	return std::pair(left, right);
}


size_t 
solve_for(size_t i, size_t depth, size_t max_depth, std::unordered_map<std::pair<size_t, size_t>, size_t, PairHash>& map){
	using namespace std;

	pair<long, long> key(i, depth);
	size_t solution = 0;


	if(depth >= max_depth){
		solution =1;
		map[key] = solution;
	}else if(map.count(key)>0){
		solution = map[key];
	}else if(i==0){
		solution = solve_for(1, depth+1, max_depth, map);
		map[key] = solution;
	}else if(digits(i) %2 ==0){
		auto split = split_size_t(i,digits(i));
		solution = solve_for(split.first, depth+1, max_depth, map) + solve_for(split.second, depth+1, max_depth, map);	
		map[key] = solution;
	}else{
		solution = solve_for(i*2024, depth+1, max_depth, map);	
		map[key] = solution;
	}

	return solution;
}



int main(int argc, char** argv){
	using namespace std;

	vector<size_t> tokens;
	fstream input("input.txt");	
	string line;
	size_t depth = 25;

	
	unordered_map<pair<size_t, size_t>, size_t, PairHash> map;

	getline(input, line);
	auto str_tokens = tokenize(line, " ");
	
	transform(str_tokens.begin(), str_tokens.end(), back_inserter(tokens), [](string str ){
			return stoi(str);
	});


	size_t sum =0;
	for(size_t i: tokens){
		sum += solve_for(i, 0, depth, map);
	}

	cout << sum << endl;
}
