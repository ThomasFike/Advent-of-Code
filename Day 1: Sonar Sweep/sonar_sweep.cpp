/*
 * @file sonar_sweep.cpp
 *  @author Thomas Fike
 */

#include <fstream>
#include <iostream>
#include <limits>

[[nodiscard]] static int get_int_from_istream(std::istream& input);

int main() {
  std::ifstream fin("input.txt");
  int number_of_times_increased = 0;
  int pervious = std::numeric_limits<int>::min();
  while (fin.good()) {
    const int current = get_int_from_istream(fin);
    if (current > pervious) {
      if (pervious != std::numeric_limits<int>::min()) {
        number_of_times_increased++;
      }
    }
    pervious = current;
  }
  std::cout << "They value was increased: " << number_of_times_increased
            << std::endl;
  fin.close();
}

[[nodiscard]] static int get_int_from_istream(std::istream& input) {
  int temp;
  input >> temp;
  return temp;
}