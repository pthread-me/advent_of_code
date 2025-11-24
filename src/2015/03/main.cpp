#include "hash.hpp"
#include <libapi.hpp>

int main(){
  pair<string, string> p1 = make_pair("AC", "CA");  
  pair<string, string> p2 = make_pair("AC", "CA");  
  pair<string, string> p3 = make_pair("CA", "AC");  

  DynamicPairHash<string, string> h;

  println("{} -- {} -- {}", h(p1), h(p2), h(p3));

}
