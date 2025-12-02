#include "io.hpp"
#include "tokenizer.hpp"
#include <cctype>
#include <cinttypes>
#include <cstdint>
#include <libapi.hpp>
#include <unordered_map>

int main(){
  auto file = read_input("2015", "07");
  unordered_map<string, uint16_t> map;
  auto literal = [](string s)-> bool{
    for(auto e: s){
      if(!isdigit(e)){
        return false;
      }
    }
    return true;
  };
  
  auto get_val = [&](string s)->ll{
    if(literal(s)){
      return stol(s);
    }else if(map.contains(s)){
        return map[s];
    }

    return -1;
  };


  auto assign = [&](string src, string dest, bool negate){
    uint16_t val;
    if(get_val(src)>-1){
      val = get_val(src);
    }else{
      return;
    }

    if(negate){
      map[dest] = ~val;
    }else{
      map[dest] = val;
    }
  };
  

  
  for(string line; getline(file, line);){
    auto tokens = tokenize<string>(line, " ");
    ull n = tokens.size();
    
    if(n==3){ 
      assign(tokens[0], tokens[2], false); 
    }else if(n==4){
      assign(tokens[1], tokens[3], true); 
    }else{
      string op = tokens[1];
      uint16_t v1 = get_val(tokens[0]);  
      uint16_t v2 = get_val(tokens[2]);  
      string dest = tokens[4];

      if(v1<0 || v2<0) continue;

      if(op == "AND"){
        map[dest] = v1 & v2;
      }else if(op == "OR"){
        map[dest] = v1 | v2;
      }else if(op == "LSHIFT"){
        map[dest] = (v1 << v2);
      }else{
        map[dest] = (v1>>v2);
      }
    }
  }
  
  for(auto [k,v]: map){
    println("{} -> {}", k, v);
  }

}
