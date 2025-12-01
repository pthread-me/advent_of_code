#include <cstring>
#include <libapi.hpp>
#include <openssl/cryptoerr_legacy.h>
#include <openssl/evp.h>

const char hex_map[] = {'0', '1', '2', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int main(){
  auto c = EVP_MD_CTX_new() ; 
  EVP_DigestInit_ex(c, EVP_md5(), NULL);

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  
  string msg = "yzbqklnj282749";

  EVP_DigestUpdate(c, msg.c_str(), msg.size());
  EVP_DigestFinal(c, md_value, &md_len);
  
  char hex[13];
  
  for(ull i=0; i<6; i++){
    unsigned int left = (md_value[i] & 0xF0) >> 4; 
    unsigned int right = (md_value[i] & 0x0F);
    println("{}, {}", left, right);
    
    hex[i] = hex_map[left];
    hex[i+1] = hex_map[right];
  }
  
  hex[12] = '\0';
  println("{}", hex);


}
