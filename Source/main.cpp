#include "big_int.h"

#include <iostream>
#include <cstdlib>

int main() {
  BigInt a(5500);
  BigInt b(22);
  BigInt empty;

  for (int i = 0; i < 50; i++) {
    a += 5500;
    std::cout << a << std::endl;
  }

  for (int i = 0; i < 100; i++) {
    a -= 5500;
    std::cout << a << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    BigInt in_test;
    std::cout << "Enter a number : " << std::endl;
    std::cin >> in_test;
    std::cout << "You just entered : " << in_test << std::endl;
  }

  empty = b - a;
  std::cout << "a is " << a << std::endl;
  std::cout << "b is " << b << std::endl;
  std::cout << "empty is " << empty << std::endl;
  empty += a;
  std::cout << "empty is now " << empty << std::endl;
  std::cout << "We got b - a as " << b - a << std::endl;
  bool my_bool = a > b;
  std::cout << "is a > b " << my_bool << std::endl;
  my_bool = a < b;
  std::cout << "is a < b " << my_bool << std::endl;
  my_bool = a < BigInt(-1);
  std::cout << "is a < -1 " << my_bool << std::endl;
  my_bool = a == b;
  std::cout << "is a == b " << my_bool << std::endl;
  system("pause");
}
