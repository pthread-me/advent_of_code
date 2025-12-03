#include "io.hpp"
#include <cryptopp/config_int.h>
#include <cryptopp/md5.h>
#include <libapi.hpp>
#include <cryptopp/cryptlib.h>
#include <string>



using namespace CryptoPP;
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1


const char hex_map[] = {'0', '1', '2', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int main (int argc, char* argv[]){
    
    ifstream file = read_input("2015", "04", SAMPLE);
    string line;
    string digest;
    getline(file, line); 
    
    Weak1::MD5 hash;
    hash.Update((const CryptoPP::byte*)&line[0], line.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);
    
    ull i = 1;
    for(; digest.substr(0, 5) != "00000"; i+=1){
      string msg = line + to_string(i);
      hash.Update((const CryptoPP::byte*)&line[0], line.size());
      digest.resize(hash.DigestSize());
      hash.Final((CryptoPP::byte*)&digest[0]);

      CryptoPP::StringSource;
      println("{}, {}", msg, digest);
    }
    
    println("{}", i-1);
}




