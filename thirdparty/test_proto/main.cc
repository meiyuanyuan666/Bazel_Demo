#include <iostream>
#include "protoc/msg.pb.h"
 
int main() {
  Im::Content msg ;
  msg.set_id(10);
  msg.set_str("mei.yuanyuan"),
  std::cout << msg.id() << '\n' << msg.str() << std::endl;
  return 0;
}