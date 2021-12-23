/**
 * @file binary_part2.cpp
 * @author Thomas Fike
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <bitset>
#include <vector>

static const int NUMBER_OF_BITS = 12;

[[nodiscard]] static std::string get_string_from_istream(std::istream& input);

[[nodiscard]] static std::bitset<NUMBER_OF_BITS> find_closet_match(
    std::vector<std::bitset<NUMBER_OF_BITS>> values, const bool most_common);

int main() {
  std::ifstream fin("input.txt");
  if (!fin.good()) {
    std::cout << "Failed to open file" << std::endl;
    return -1;
  }

  std::vector<std::bitset<NUMBER_OF_BITS>> values;
  values.reserve(2000);
  while (fin.good()) {
    values.emplace_back(get_string_from_istream(fin));
  }

  const auto O2_found = find_closet_match(values, true).to_ulong();
  const auto CO2_found = find_closet_match(values, false).to_ulong();

  std::cout << "O2, CO2: " << O2_found << ", " << CO2_found << std::endl;
  std::cout << "Answer: " << (O2_found * CO2_found) << std::endl;
  fin.close();
}

[[nodiscard]] static std::string get_string_from_istream(std::istream& input) {
  std::string temp;
  input >> temp;
  return temp;
}

[[nodiscard]] static std::bitset<NUMBER_OF_BITS> find_closet_match(
    std::vector<std::bitset<NUMBER_OF_BITS>> values, const bool most_common) {
  int i = NUMBER_OF_BITS - 1;
  while (values.size() >= 2) {
    auto checker = [i](std::bitset<NUMBER_OF_BITS> value) {
      return (value[i] == true);
    };
    const auto amount_true =
        std::count_if(values.begin(), values.end(), checker);
    const auto amount_false = (values.size() - amount_true);
    bool expected_value = false;
    if (amount_true >= amount_false) {
      expected_value = most_common;
    } else {
      expected_value = !most_common;
    }
    auto new_checker = [i, expected_value](std::bitset<NUMBER_OF_BITS> value) {
      return (value[i] != expected_value);
    };
    values.erase(std::remove_if(values.begin(), values.end(), new_checker),
                 values.end());
    i--;
  }
  return values[0];
}