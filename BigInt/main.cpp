#include "big_int.h"

#include <iostream>
#include <cstdlib>

int main() {

  BigInt a(5500);
  BigInt b(22);
  BigInt empty;
  empty = b-a;
  std::cout << "a is " << a << std::endl;
  std::cout << "b is " << b << std::endl;
  std::cout<< "empty is" << empty << std::endl;
  empty += a;
  std::cout<< "empty is now" << empty << std::endl;
  std::cout << "We got b - a" << b - a << std::endl;
  bool my_bool = a > b;
  std::cout << "is a > b " << my_bool << std::endl;
  my_bool = a < b;
  std::cout << "is a < b " << my_bool << std::endl;
  my_bool = a < BigInt(-1);
  std::cout << "is a < -1 " << my_bool << std::endl;
  my_bool = a==b;
  std::cout << "is a == b " << my_bool<< std::endl;
  system("pause");
}
