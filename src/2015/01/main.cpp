#include <libapi.hpp>

inline ll evaluate_string(char c){
  if(c == '(') return 1;

  return -1;
}


int main(){
  
  ifstream file = read_input("2015", "01");
  string raw_input;
  getline(file, raw_input);


  string_view input = string_view(raw_input);


  ll p = 0;

  for(ll i=0; i<input.size(); ++i){
    p += evaluate_string(input[i]);
    if(p<0){
      print("Negative p: {}  at block starting at {}\n",p, i+1);
      break;
    }
  }

}
