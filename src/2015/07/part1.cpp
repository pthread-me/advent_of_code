#include "tokenizer.hpp"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <libapi.hpp>
#include <unordered_map>


bool is_numeric(string s){
	bool numeric = true;
	for(char c: s){
		if(!isdigit(c)){
			numeric = false;
			break;
		}
	}

	return numeric;
}


uint16_t evaluate(string k, unordered_map<string, uint16_t>& values, unordered_map<string, vector<string>>& expressions){
	if(values.contains(k)){
		return values[k];
	}else if(is_numeric(k)){
		return token_cast<uint16_t>(k);
	}

	auto expr = expressions[k];
	ull n = expr.size();
	
	
	if(n==1 || n==2){
		string src;
		bool negate;
		uint16_t res;

		if(expr[0] == "NOT"){
			src = expr[1];	
			negate = true;
		}else{
			src = expr[0];
			negate = false;
		}
	
    if(negate){
      values[k] = ~evaluate(src, values, expressions);
    }else{
      values[k] = evaluate(src, values, expressions);
    }

	}else{
		uint16_t r1 = evaluate(expr[0], values, expressions);	
		uint16_t r2 = evaluate(expr[2], values, expressions);	
		string op = expr[1];

		if(op == "AND"){
			values[k] = r1 & r2;	
		}else if(op == "OR"){
			values[k] = r1 | r2;
		}else if(op == "LSHIFT"){
			values[k] = r1 << r2;
		}else{
			values[k] = r1 >> r2;
		}
	}
	
	return values[k];
}

int main(){
  ifstream file = read_input("2015", "07", INPUT);
  unordered_map<string, uint16_t> values;
  unordered_map<string, vector<string>> expressions;

  for(string line; getline(file, line);){
    auto tokens = tokenize<string>(line, " ");
    ull n = tokens.size();

    expressions[tokens[n-1]] = vector<string>();
    copy_n(tokens.begin(), n-2, back_inserter(expressions[tokens[n-1]]));
  }


		uint16_t res = evaluate("a", values, expressions);
		println("{}: {}", "a", res);

}

