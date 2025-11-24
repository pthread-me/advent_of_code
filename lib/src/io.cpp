#include <definitions.hpp>
#include <io.hpp>

/**
 * Usage example (2023, 01) to read input.txt from 
 * folder 2023 day 01
 * No checks are made to ensure the file exists, use get.sh to create
 */
ifstream read_input(string year, string day){
  string file_name("inputs/"+year+"/"+day+"/input.txt");
  ifstream file = ifstream(file_name);

  if(!file.is_open()){
    println(stderr, "File: {} does not exist. try running get.sh ", file_name);
    throw runtime_error("File not found");
  }

  return file;
}


