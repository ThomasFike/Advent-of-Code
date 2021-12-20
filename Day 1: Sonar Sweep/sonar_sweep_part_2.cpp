/*
 * @file sonar_sweep_part_2.cpp
 * @author Thomas Fike
 */

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

static constexpr int minimum_vector_length = 2000;

[[nodiscard]] static int get_int_from_istream(std::istream& input);

int main() {
  std::ifstream fin("input.txt");
  std::vector<int> values;
  values.reserve(minimum_vector_length);
  while (fin.good()) {
    values.push_back(get_int_from_istream(fin));
  }
  std::vector<int> averages;
  averages.reserve(3 * (values.size() - 4));
  for (unsigned int i = 0; i < values.size(); i += 3) {
    if ((i + 2) < values.size()) {
      averages.push_back(values[i] + values[i + 1] + values[i + 2]);
    }
    if ((i + 3) < values.size()) {
      averages.push_back(values[i + 1] + values[i + 2] + values[i + 3]);
    }
    if ((i + 4) < values.size()) {
      averages.push_back(values[i + 2] + values[i + 3] + values[i + 4]);
    }
  }
  int number_of_time_increased = 0;
  for (unsigned int i = 0; i < averages.size() - 1; i++) {
    if (averages[i] < averages[i + 1]) {
      number_of_time_increased++;
    }
  }
  fin.close();
  std::cout << "Increased: " << number_of_time_increased << std::endl;
}

[[nodiscard]] static int get_int_from_istream(std::istream& input) {
  int temp;
  input >> temp;
  return temp;
}