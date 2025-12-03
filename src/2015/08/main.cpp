#include <libapi.hpp>


ull count(string l){
  ull res = 2;
  
  for(ull i=0; i<l.size(); i++){
    if(l[i] == '\"' || l[i] == '\\'){
      res +=2;
    }else{
      res += 1;
    }
  }

 return res;
}

int main(){
  ifstream file = read_input("2015", "08", INPUT);
  ull original = 0;
  ull updated = 0;

  for(string line; getline(file, line);){
    original += line.size();
    updated += count(line);
  }

  ull diff = updated-original;
  println("{} - {} = {}", updated, original, diff);
}
