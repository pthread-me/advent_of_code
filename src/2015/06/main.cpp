#include "hash.hpp"
#include "tokenizer.hpp"
#include <libapi.hpp>


int main(){
  ifstream file = read_input("2015", "06");

  static_pair_map<ull, ull, ull> map;

  auto toggle = [&](pair<ull, ull> pos){
    if(map.contains(pos)){
      map[pos] += 2;
    }else{
      map[pos] = 2;
    }
  };

  auto off = [&](pair<ull, ull> pos){
    if(map.contains(pos)){
      map[pos] = map[pos]>0 ? map[pos]-1: 0;
    }
  };

  auto on = [&](pair<ull, ull> pos){
    if(map.contains(pos)){
      map[pos] ++;
    }else{
      map[pos] = 1;
    }
  };

  
  for(string line; getline(file, line);){
    auto l1 = tokenize<string,5>(line, " ");   
    if(l1[0] == "turn") l1.erase(l1.begin());

    auto l2 = tokenize<ull, 2>(l1[1], ","); 
    auto l3 = tokenize<ull, 2>(l1[3], ","); 

    string action = l1[0];
    pair<ull, ull> s = {l2[0], l2[1]};
    pair<ull, ull> e = {l3[0], l3[1]};
    
    for(ull i=s.first; i<=e.first; i++){
      for(ull j=s.second; j<=e.second; j++){
        if(action == "on"){
          on({i,j});
        }else if (action == "off") {
          off({i,j});
        }else{
          toggle({i,j});
        }
      }
    
    }
  }
  
  ull res = 0;
  for(auto [k, v]: map){
    res += v; 
  }
  println("{}", res);
}
