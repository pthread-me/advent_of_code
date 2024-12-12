#include <numeric>
#include <type_traits>
#include <vector>
#include <iostream>


class Solution{
	public:
		int l = 12;

		int chalkReplacer(std::vector<int>& chalk, int k){
			int chalk_size = chalk.size();
			int sum = 0;
			
			//find sum until it exceeds K
			for(auto x : chalk){
				sum += x;
				if(sum > k){
					sum = k+1;
					break;
				}
			}


			k = k>sum ? k%sum : k;
			int index =0;
			while(chalk[index] <= k){
				k -= chalk[index];
				index = (index+1) % chalk_size;
			}

			return index;	
		}
};


int main(){

	std::vector<int> chalk = {5,1,5};
	int k = 22;

	Solution S = Solution();
	std::cout << S.chalkReplacer(chalk, k);

	return 0;
}