#include "io.hpp"
#include <cryptopp/config_int.h>
#include <cryptopp/filters.h>
#include <cryptopp/md5.h>
#include <libapi.hpp>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <print>
#include <string>



using namespace CryptoPP;
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1



int main (int argc, char* argv[]){
    
    ifstream file = read_input("2015", "04", INPUT);
    string line;


    CryptoPP::byte digest[Weak1::MD5::DIGESTSIZE];
    getline(file, line); 
    string hex_digest;
    
    Weak1::MD5 hash;
    CryptoPP::HexEncoder encoder;

    auto get_digest = [&](string msg){
      encoder.Attach(new StringSink(hex_digest));
      hash.CalculateDigest(digest, (CryptoPP::byte*)&msg[0] , msg.size());
      encoder.PutMessageEnd(digest, Weak1::MD5::DIGESTSIZE);
      println("{}", hex_digest);
    };
    
  
    ull i = 1;
    while(true){
      get_digest(line + to_string(i)); 
      if(hex_digest.substr(0, 6) == "000000"){
        println("{}", i);
        break;
      }
      i+=1;
      hex_digest.clear();
    }
}




