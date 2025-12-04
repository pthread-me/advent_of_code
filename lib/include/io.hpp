#include <definitions.hpp>

#pragma once
#ifndef MyIO
#define MyIO


enum FileType{
	INPUT = 0,
	SAMPLE
};

/**
 * Usage example (2023, 01) to read input.txt from 
 * folder 2023 day 01
 * No checks are made to ensure the file exists, use get.sh to create
 */
inline ifstream read_input(string year, string day, FileType t){
  string src = t==INPUT?"input.txt":"sample.txt";
  string file_name("inputs/"+year+"/"+day+"/"+src);
  ifstream file = ifstream(file_name);

  if(!file.is_open()){
    println(stderr, "File: {} does not exist. try running get.sh ", file_name);
    throw runtime_error("File not found");
  }

  return file;
}




#endif
