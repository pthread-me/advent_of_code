#include "hash.hpp"
#include "tokenizer.hpp"
#include <libapi.hpp>
#include <ranges>
#include <unordered_set>


ull part1(vector<vector<char>>& grid, ull i, ull j, unordered_map<pair<ull, ull>,ull, StaticPairHash<ull, ull>>& dp){
  while(i+1<grid.size() and grid[i+1][j] != '^'){
    i+=1;
  }

  if(i==grid.size()-1){
    return 1;
  }
  
  if(dp.contains({i,j})){
    return dp[{i,j}];
  }

  ull left = 0;
  ull right = 0;

  if(j-1<grid[0].size()){
    left = part1(grid, i+1, j-1, dp);
  } 
  if(j+1<grid[0].size()){
    right = part1(grid, i+1, j+1, dp);
  }
  
  dp[{i,j}] = left + right;
  return  left + right;
}

int main(){
  ifstream file = read_input("2025", "07", INPUT);
  vector<vector<char>> grid;
  auto dp = unordered_map<pair<ull, ull>, ull, StaticPairHash<ull, ull>>();
  
  for(string line; getline(file, line);){
    vector<char> row;
    for(char e: line){
      row.push_back(e); 
    }
    grid.push_back(row);
  }

  ull j = 0;
  for(auto [i,v]: srv::enumerate(grid[0])){
    if(v == 'S'){
      j = i;
      break;
    }
  }


  ull res = part1(grid,0,j, dp);
  println("{}", res);
}
