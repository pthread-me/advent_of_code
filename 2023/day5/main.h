#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>


const int base = 10;
#define NUMBER_OF_SEEDS 20 
const int MAX_MAP_SIZE = 50;
const long MAX_LONG = powl(2,63)-1;
const char delim = ' ';



#ifndef main_header
#define main_header
typedef struct Mapping{
	long* src_start;
	long* src_end;
	long* des_start;
	long* des_end;
	int map_size;
}Map;

Map** create_map();
long map_stack_check(Map**, long);

#endif


