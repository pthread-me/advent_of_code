#ifndef DEFINITIONS 
#define DEFINITIONS

// C lib and why
#include <string.h>	// for strtok
#include <cstdlib>	// for strto<number> 
#include <cstring>	// tokenizers


// Misc
#include <print>
#include <fstream>
#include <string>
#include <type_traits>

// Algs and DS
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>

using namespace std;

// Type defines
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;


// Concepts
template<typename T>
concept signed_long = is_arithmetic_v<T> && is_signed_v<T>;

template<typename T>
concept unsigned_long = is_arithmetic_v<T> && is_signed_v<T>;

template<typename T>
concept castable = is_arithmetic_v<T>;

template<typename T>
concept not_castable_string = !is_arithmetic_v<T> && is_same_v<T, string>;

template<typename T>
concept not_castable = !is_arithmetic_v<T>;



#endif
