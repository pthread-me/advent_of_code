#include <iostream>
#ifndef MAP_DEFINITION 
#define  MAP_DEFINITION

class Map {

	public:
		long dest_start;
		long src_start;
		long range;

		Map(long, long, long);	
		~Map();

		const long mapping(long seed, Map map);
		const int mapping_compare(Map a, Map b);
};
#endif
