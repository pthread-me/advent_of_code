#ifndef MyIO
#define MyIO
#include <definitions.hpp>

enum FileType{
	INPUT = 0,
	SAMPLE
};

ifstream read_input(string year, string day, FileType t);

#endif
