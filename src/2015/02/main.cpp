#include <libapi.hpp>

int main(){
  ifstream file = read_input("2015", "02");  
  array<string, 3> tokens = array<string, 3>();
  array<ull, 3> dim = array<ull, 3>();
  ull feet = 0;



  string delim("x");
  string line("-12x1x00");
  auto a = tokenize<ll, ll(3)>(line, delim);
  for(auto e: a){
    print("{}, ", e);
  }

  /*
  for(string line; getline(file, line);){
    dim = tokenize<ull, 3>(line, delim);

    for(ull e: dim){
      print("{}, ", e);
    }
    print("\n");
  }
  */
  
}
