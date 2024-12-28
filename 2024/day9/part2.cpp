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

	vector<int> line;
	transform(str_line.begin(), str_line.end(), back_inserter(line), [](char c){
		return c - '0';	
	});

	// left pointer, index, val, val len, gap len, right block, block len, end pointer. short names => easier to debug in gdb 
	int p, i, v, vl, gl, b, bv, bl, ep;
	long sum;
	
	p=0, i=0, v=0, gl=0, sum=0;
	vl = line[p];	
	b = line.size()%2==0? line.size()-2: line.size()-1;	
	ep =b;
	bv = b/2;
	bl = line[b];

	
	while(p<line.size()){
		if(vl >= 1){
			sum += i*v;
			vl--;
			i++;
		}else if(vl<0){
			i+= abs(vl);
			vl = 0;
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
		}else{

			int bl_neg=0;
			while(gl>0){
				if(bl>=1 && bl <= gl){
					sum += i*bv;
					bl--;
					line[b]--;
					bl_neg--;
					gl--;
					i++;

					if(bl==0){
						line[b] = bl_neg;
						bl_neg=0;
					}
				}else{
					size_t cur_b = b;	
					for(int j=ep; j>p; j-=2){
						if (line[j] <= gl && line[j]>=1){
							b = j;
							bl = line[b];
							bv = b/2;
							break;
						}
					}
					if(b == cur_b){
						i+=gl;
						gl=0;
					}
				}
			}
		} 
	}

	cout << sum << endl;
}
