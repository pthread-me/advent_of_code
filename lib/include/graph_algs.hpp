// Main Algorithm from : https://www.onlycode.in/travelling-salesman-problem-using-held-karp-algorithm-dynamic-programming/

#pragma once
#include <algorithm>
#include <definitions.hpp>
#include <vector>

namespace GraphAlgs{

const ull MAX_EDGE_WEIGHT = 999;
const ull INF = MAX_ULL - MAX_EDGE_WEIGHT;


/*
 * Traveling Salesman Problem
 *	returns (mincost, pointer to shortest path)
 */
inline
auto tsp(vector<vector<ull>>& grid)
-> pair<ull, vector<ull>*>{

  ull n = grid.size(); 
  ull cardinality = (1<<n);

  // 2^n rows each row with n columns for the possible ending vertex of that subset
  vector<vector<ull>> dp = vector(cardinality, vector(n, INF));
  dp[1][0] = 0;
	
	vector<vector<ull>> paths =  vector<vector<ull>>(cardinality, vector<ull>(n, INF));
  
  // filling the dp with all possible minimal paths for each subset ending at 
  // each node
  for(ull mask = 1; mask<(cardinality); ++mask){

    // Given a path that currently ends at vertex i, we want to find the next step j
    for(ull i = 0; i<n; ++i){
      // skip i if its not in the Set
      if(!(mask& (1<<i))) continue;
     
      // find the minimal path to j given a path that ends at i
      for(ull j=0; j<n; ++j){
        if(!(mask & (1<<j) || i==j)) continue;
        
        if(dp[mask][j] > dp[mask^(1<<j)][i]+grid[i][j]){
          dp[mask][j] =(dp[mask^(1<<j)][i]+grid[i][j]);
          paths[mask][j] = i;
        }
      }
    }
  }

  

  // Finding the minimal path
  ull min_cost = INF;
  ll last_node = -1;
  vector<ull>* tour = new vector<ull>();
  ull mask = cardinality -1;
  
  (*tour).push_back(0);
  
  // minimum path is that where the sum of P ending at i + (i,0) is minimized
  for(ull i = 0; i<n; ++i){
    if(min_cost>dp[mask][i] + grid[i][0]){
      min_cost = dp[mask][i] + grid[i][0]; 
      last_node = i;
    }
  }
  
  // we build it from the end to the start
  while(last_node != 0){
    (*tour).push_back(last_node);
    ull prev_node = paths[mask][last_node];
    mask ^= (1<<last_node);
    last_node = prev_node;
  }

  (*tour).push_back(0);

  reverse(tour->begin(), tour->end());
  return {min_cost, tour};
}




inline
pair<ll, vector<ll>> bellman_ford(vector<vector<ll>> grid){
  //Todo!
  return pair{-1, vector<ll>()};
}

}
