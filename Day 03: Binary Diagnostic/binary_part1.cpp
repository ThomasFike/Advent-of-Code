/**
 * @file binary_part1.cpp
 * @author Thomas Fike
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

[[nodiscard]] static std::string get_string_from_istream(std::istream& input);

int main() {
  std::ifstream fin("input.txt");
  if (!fin.good()) {
    std::cout << "Failed to open file" << std::endl;
    return -1;
  }

  std::string first_line;
  fin >> first_line;
  const int number_of_bits = first_line.length();
  fin.seekg(0);

  std::vector<int> sum_per_position(number_of_bits);
  std::fill(sum_per_position.begin(), sum_per_position.end(), 0);
  int number_of_values = 0;

  while (fin.good()) {
    const std::string current = get_string_from_istream(fin);
    for (int i = 0; i < number_of_bits; i++) {
      if (current[i] == '1') {
        sum_per_position[i]++;
      }
    }
    number_of_values++;
  }
  int gamma_rate = 0;
  int epsilon_rate = 0;
  for (int i = 0; i < number_of_bits; i++) {
    if ((sum_per_position[i] / float(number_of_values)) > 0.5) {
      gamma_rate |= (1 << (number_of_bits - i - 1));
    } else {
      epsilon_rate |= (1 << (number_of_bits - i - 1));
    }
  }
  std::cout << epsilon_rate << std::endl;
  std::cout << "Power: " << (gamma_rate * epsilon_rate) << std::endl;
}

[[nodiscard]] static std::string get_string_from_istream(std::istream& input) {
  std::string temp;
  input >> temp;
  return temp;
}