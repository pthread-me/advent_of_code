#pragma once
#ifndef DEFINITIONS 
#define DEFINITIONS

// C lib and why
#include <concepts>
#include <cstring>	// for strtok
#include <cstdlib>	// for strto<number> 
#include <cstring>	// tokenizers
#include <climits>  // max ints etc

// Misc
#include <expected>
#include <print>
#include <fstream>
#include <string>
#include <type_traits>

// Algs and DS
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <array>
#include <ranges>
#include <numeric>
#include <functional>
#include <algorithm>


using namespace std;
namespace sr = ranges;
namespace srv = ranges::views;

// Type defines
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;


const ull MAX_ULL = ULLONG_MAX; 
const ll MIN_LL = LLONG_MIN;
const ll MAX_LL = LLONG_MAX;
const ull MAX_GR  = 0x9e3779b97f4a7c15ULL; // 2^64/golden ratio




// Concepts
template<typename T>
concept signed_long = is_arithmetic_v<T> && is_signed_v<T>;

template<typename T>
concept unsigned_long = is_arithmetic_v<T> && is_unsigned_v<T>;

template<typename T>
concept castable = is_arithmetic_v<T>;

template<typename T>
concept String = is_same_v<T, string>;

template<typename T>
concept hashable = is_arithmetic_v<T> ||  same_as<T, string>;

#endif
