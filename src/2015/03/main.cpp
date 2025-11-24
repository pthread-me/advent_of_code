#include <libapi.hpp>
#include <utility>

int main(){
  unordered_set<pair<ll, ll>, StaticPairHash<ll, ll>> dp; 
  ifstream file = read_input("2015", "03");
  string line;

  getline(file, line);
  pair<ll, ll> pos = make_pair(0, 0);
  pair<ll, ll> s_pos = make_pair(0, 0);
  pair<ll, ll> r_pos = make_pair(0, 0);
  bool is_santa = true;

  dp.insert(pos);

  for(char c: line){
    if(is_santa){
      pos = s_pos;
    }else{
      pos = r_pos;
    }

    switch (c) {
      case '>': pos.second+=1; break;
      case '<': pos.second-=1; break;
      case '^': pos.first+=1; break;
      case 'v': pos.first-=1; break;
      default: print(stderr, "hit unreachable\n"); exit(-1); 
     } 
    dp.insert(pos);
    
    if(is_santa){
      s_pos = pos;
    }else{
      r_pos = pos;
    }

    is_santa = !is_santa;
  }

  println("size: {}", dp.size());
  
}
