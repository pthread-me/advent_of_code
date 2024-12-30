#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

int main(){
	using namespace std;

	fstream input("input.txt");
	string str_line;
	getline(input, str_line);

	vector<size_t> line;
	transform(str_line.begin(), str_line.end(), back_inserter(line), [](char c){
		return c - '0';	
	});

	// left pointer, index, val, val len, gap len, right block, block len. short names => easier to debug in gdb 
	size_t p, i, v, vl, gl, b, bv, bl, sum;
	
	p=0, i=0, v=0, gl=0, sum=0;
	vl = line[p];	
	b = line.size()%2==0? line.size()-2: line.size()-1;	
	bv = b/2;
	bl = line[b];

	
	while(p<=b){
		if(bv==v && bl != vl){
			vl = bl;
		}else if(vl >= 1){
			sum += i*v;
			vl--;
			i++;
			if(bv == v){
				bl--;
			}
		}else if(gl==0){
			if(p%2==0){
				p++;
				gl=line[p];
			}else{
				p++;
				v++;
				vl = line[p];
			}
			continue;
		}else if(bl>=1){
			sum += i*bv;
			bl--;
			gl--;
			i++;
		
		}else{
			b-=2;
			bv --;
			bl = line[b];
			continue;
		}
	}

	cout << sum << endl;
}
