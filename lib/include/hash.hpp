#ifndef HASHERS
#define HASHERS
#include <definitions.hpp>
#include<rapidhash.h>



template<typename T>
concept StaticSized = is_arithmetic_v<T>;


template<typename T>
concept DynamicSized = is_same_v<T,  string> || is_same_v<T, string_view>;

template<StaticSized A, StaticSized B>
class StaticPairHash{
	private:
	  
    char* buffer;
    ull buffer_len;

	public:
		StaticPairHash(){
      buffer_len =  sizeof(A)+ sizeof(B);
      buffer = (char*) calloc(0, buffer_len);
    }

		size_t operator()(const pair<A, B>& p){
      memcpy(buffer, &p.first, sizeof(A));
      memcpy(&(buffer[sizeof(A)]), &p.second, sizeof(B));
      
			return rapidhash(buffer, buffer_len);
		}
 
};


template<DynamicSized A, DynamicSized B>
class DynamicPairHash{
	public:

    DynamicPairHash(){}

    size_t operator()(const pair<A, B>& p){
      ull buffer_len =  p.first.size() + p.second.size();
      char* buffer = (char*) calloc(0, buffer_len);

      memcpy(buffer, p.first.c_str(), p.first.size());
      memcpy(&(buffer[p.first.size()]), p.second.c_str(), p.second.size());
      
      return rapidhash(buffer, buffer_len);
    }
 
};



#endif
