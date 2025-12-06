#include "TSP.hpp"
#include "hash.hpp"
#include "tokenizer.hpp"
#include <libapi.hpp>
#include <unordered_map>


int main(){
  ifstream file = read_input("2015", "09", INPUT);
  
  unordered_map<string, ull> name_to_index;
  unordered_map<pair<ull,ull>, ull, StaticPairHash<ull, ull>> edge_value;
  ull counter = 0;
	/*
  for(string line; getline(file, line);){
    auto tokens = tokenize<string>(line, " ");
    if(!name_to_index.contains(tokens[0])){
      name_to_index[tokens[0]] = counter;
      counter ++;
    }
    if(!name_to_index.contains(tokens[2])){
      name_to_index[tokens[2]] = counter;
      counter ++;
    }
    edge_value[{name_to_index[tokens[0]], name_to_index[tokens[2]]}] = token_cast<ull>(tokens[4]);
  }


 
  vector<vector<ull>> grid = vector(counter, vector(counter, TSP::INF));
  for(auto [k,v]: edge_value){
    grid[k.first][k.second] = v; 
  }
*/


    vector<vector<ull>> grid = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0}
    };
  
  for(auto [k,v]: name_to_index){
    println("{} = {}", k, v);
  }
  println();



  for(auto r: grid){
    println("{}", r);
  }

  
  auto [min_cost, tour] = TSP::tsp_path(grid); 
  println("Min cost was: {}", min_cost);

  for(auto e: *tour){
    print("{} -> ", e); 
  }
}
