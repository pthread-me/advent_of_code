#ifndef TOKENIZER
#define TOKENIZER

#include <definitions.hpp>


template<unsigned_long T, ull size>
inline T token_cast(char* s){
  char* str_end;
  ll res = strtoull(s, &str_end, 10);
  if(errno == ERANGE){
    print(stderr, "{} 's conversion is out of range for a long long\n", s);
    throw runtime_error("Out of range long long cast");
  }
  return res;
}

template<signed_long T>
inline T token_cast(char* s){
  char* str_end;
  ll res = strtoll(s, &str_end, 10);
  if(errno == ERANGE){
    print(stderr, "{} 's conversion is out of range for a long long\n", s);
    throw runtime_error("Out of range long long cast");
  }
  return res;
}

template<not_castable_string T>
inline T token_cast(char* s){return s;}

template<not_castable T>
inline T token_cast(char* s){
  print(stderr, "Type T: {} is not castable. Write a custome function to cast char* -> T", typeid(T).name() );
  throw runtime_error("casting error");
}


template<typename T, ull size> 
array<T, size> tokenize(const string& line, const string& delim ){
  array<T, size> res;

  // +1 since .size() does not account for the \0
  char *s = (char*)calloc(line.size()  +1, sizeof(char));
  char *d = (char*)calloc(delim.size() +1, sizeof(char));
  char *token = (char*)calloc(line.size(), sizeof(char));

  strlcpy(s, line.c_str(), line.size()    +1);
  strlcpy(d, delim.c_str(), delim.size()  +1);
  
  token = strtok(s, d);
  for(ull i=0; i<size; ++i){
    res[i] = token_cast<T>(token); 
    token = strtok(NULL, d);
  }
  
  return res;
}

#endif
