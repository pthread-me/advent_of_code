#include <libapi.hpp>

int main(){
  ifstream file = read_input("2015", "02");  
  array<string, 3> tokens = array<string, 3>();
  array<ull, 3> dim = array<ull, 3>();

  ull feet = 0;
  string delim("x");

  for(string line; getline(file, line);){
    dim = tokenize<ull, 3>(line, delim);
    ull min = MAX_ULL;  
    
    for(ull i=0; i<3; ++i){
      ull mul = dim[i] + dim[(i+1)%3];
      min = min<(2*mul)? min : (2*mul);
    }


    println("min = {}", min);
    feet += (min);
    feet += (dim[0]*dim[1]*dim[2]);
  }

  print("{}\n", feet);
}
