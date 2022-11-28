#include <iostream>

#include "common.hpp"

int main() {
  std::cout << "Hello World" << std::endl;
  const std::vector<int> var = {1, 2, 3};
  print_vector(var);
  // auto a = 1;
  return -1;
}