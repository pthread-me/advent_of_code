#include <libapi.hpp>


ull count(string l){
 ull res = 0;
  
 for(ull i=1; i<l.size()-1; i++){
    if(l[i] == '\\'){
      if(l[i+1] == '\\' || l[i+1]!='x'){
        i+=1;
        res += 1;
      }else{
        i+=3;
        res += 1;
      }

    }else{
      res += 1;
    }
 }

 return res;
}

int main(){
  ifstream file = read_input("2015", "08", INPUT);
  ull original = 0;
  ull memory = 0;

  for(string line; getline(file, line);){
    original += line.size();
    memory += count(line);
  }

  ull diff = original-memory;
  println("{} - {} = {}", original, memory, diff);
}
