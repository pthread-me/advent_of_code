#include "map.hpp"
using namespace std;

Map::Map(long dest, long src, long range): dest_start(dest), src_start(src), range(range){}

Map::~Map(){}

const long mapping(long seed, Map map){
	return 0l;
}

const int mapping_compare (long seed, const Map b){
	if(seed < b.src_start){
		return -1;
	}else if(seed > b.src_start + b.range -1){
		return 1;
	}
	return 0;
}


