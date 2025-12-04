#pragma once
#ifndef TOKENIZER
#define TOKENIZER

#include <definitions.hpp>


template<unsigned_long T>
inline T c_token_cast(char* s){
  char* str_end;
  ll res = strtoull(s, &str_end, 10);
  if(errno == ERANGE){
    print(stderr, "{} 's conversion is out of range for a long long\n", s);
    throw runtime_error("Out of range long long cast");
  }
  return res;
}

template<signed_long T>
inline T c_token_cast(char* s){
  char* str_end;
  ll res = strtoll(s, &str_end, 10);
  if(errno == ERANGE){
    print(stderr, "{} 's conversion is out of range for a long long\n", s);
    throw runtime_error("Out of range long long cast");
  }
  return res;
}

template<String T>
inline T c_token_cast(char* s){return s;}



template<typename T>
inline T token_cast(string& line){
  char *s = (char*)calloc(line.size()  +1, sizeof(char));
  strlcpy(s, line.c_str(), line.size()    +1);
	return c_token_cast<T>(s);
}


template<typename T, ull size=0> 
vector<T> tokenize(const string& line, const string& delim ){
  vector<T> res;
	res.reserve(size);

  // +1 since .size() does not account for the \0
  char *s = (char*)calloc(line.size()  +1, sizeof(char));
  char *d = (char*)calloc(delim.size() +1, sizeof(char));
  char *token = (char*)calloc(line.size(), sizeof(char));

  strlcpy(s, line.c_str(), line.size()    +1);
  strlcpy(d, delim.c_str(), delim.size()  +1);
  
  token = strtok(s, d);
  while(token!=NULL){
    res.push_back(c_token_cast<T>(token)); 
    token = strtok(NULL, d);
  }
  
  return res;
}

#endif
