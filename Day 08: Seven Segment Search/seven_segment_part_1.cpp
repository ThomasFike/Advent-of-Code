/**
 * @file seven_segment_part_1.cpp
 * @author Thomas Fike
 */

#include "../reuse.hpp"

#include <string>
#include <sstream>
#include <map>

static const std::map<int, int> num_chars_to_value = {
    {2, 1}, {4, 4}, {3, 7}, {7, 8}};

int main() {
  std::vector<std::string> strings;
  strings.reserve(100);
  {
    std::ifstream input_file("input.txt");
    if (!input_file.good()) {
      std::cout << "Could not open file" << std::endl;
      return 1;
    }

    while (input_file.good()) {
      std::string first_part;
      std::getline(input_file, first_part, '|');
      std::string second_part;
      std::getline(input_file, second_part);
      std::stringstream second_stream(second_part);
      while (second_stream.good()) {
        std::string temp;
        second_stream >> temp;
        strings.emplace_back(temp);
      }
    }
  }
  int counter = 0;
  for (const auto& i : strings) {
    if (num_chars_to_value.find(i.length()) != num_chars_to_value.end()) {
      counter++;
    }
  }
  std::cout << "Found 1,4,7,8: " << counter << " Times" << std::endl;
}