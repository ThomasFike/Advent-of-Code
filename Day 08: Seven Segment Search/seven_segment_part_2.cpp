/**
 * @file seven_segment_part_2.cpp
 * @author Thomas Fike
 */

#include "../reuse.hpp"

#include <string>
#include <sstream>
#include <map>
#include <exception>
#include <cmath>

template <typename T1, typename T2>
void print_map(const std::map<T1, T2>& m) {
  for (const auto& [key, value] : m) {
    std::cout << key << " = " << value << "; ";
  }
  std::cout << "\n";
}

static const std::map<int, int> num_chars_to_value = {
    {2, 1}, {4, 4}, {3, 7}, {7, 8}};

static const std::map<std::string, int> standard_segment_map = {
    {"abcefg", 0}, {"cf", 1},     {"acdeg", 2}, {"acdfg", 3},   {"bcdf", 4},
    {"abdfg", 5},  {"abdefg", 6}, {"acf", 7},   {"abcdefg", 8}, {"abcdfg", 9}};

std::map<char, char> generate_conversion_map(
    std::array<std::string, 10> inputs);
bool are_all_chars_contained(const std::string reference,
                             const std::string check);
std::map<std::string, int> generate_segment_map(
    const std::map<char, char> conversion_map);

int main() {
  std::vector<std::array<std::string, 10>> inputs;
  std::vector<std::array<std::string, 4>> outputs;
  outputs.reserve(200);
  inputs.reserve(200);
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
      std::stringstream first_stream(first_part);
      std::stringstream second_stream(second_part);
      std::array<std::string, 10> input;
      std::array<std::string, 4> output;
      for (auto& i : input) {
        first_stream >> i;
      }
      for (auto& i : output) {
        second_stream >> i;
      }
      inputs.emplace_back(input);
      outputs.emplace_back(output);
    }
  }
  int sum = 0;
  for (unsigned int i = 0; i < inputs.size(); i++) {
    const auto conversion_map = generate_conversion_map(inputs[i]);
    const auto segment_map = generate_segment_map(conversion_map);
    for (int j = 0; j < 4; j++) {
      std::string segments = outputs[i][j];
      std::sort(segments.begin(), segments.end());
      try {
        const int value = segment_map.at(segments);
        sum += (value * pow(10, (3 - j)));
      } catch (...) {
        std::cout << "Failed to convert!" << std::endl;
      }
    }
  }
  std::cout << "SUM: " << sum << std::endl;
}  // main()

/**
 * @brief Generates a maping between the expected segments and the real
 * segments.
 * @details Goes through and trys to determine which strings in the input are
 * what number. Along the way the map is generated and used in this process.
 * This is a quite complex method that could use some optimization but works for
 * now.
 *
 * @param input_array Array from the input with all 10 input strings.
 * @return std::map<char, char> map<expected_segment, real_segment>
 */
std::map<char, char> generate_conversion_map(
    const std::array<std::string, 10> input_array) {
  std::vector<std::string> inputs(input_array.begin(), input_array.end());
  std::map<char, char> mapping;
  std::map<int, std::string> known_strings;
  for (const auto& str : inputs) {
    try {
      switch (num_chars_to_value.at(str.length())) {
        case 1:
          known_strings[1] = str;
          break;
        case 4:
          known_strings[4] = str;
          break;
        case 7:
          known_strings[7] = str;
          break;
        case 8:
          known_strings[8] = str;
        default:
          break;
      }
    } catch (...) {
    }
  }
  // Remove elements that are already in the map.
  auto remove_existing_elements = [&known_strings, &inputs]() {
    for (const auto& item : known_strings) {
      inputs.erase(std::remove(inputs.begin(), inputs.end(), item.second),
                   inputs.end());
    }
  };
  remove_existing_elements();
  // Solve for a by finding what is in 7 but not in 4
  for (const char a_candiate : known_strings[7]) {
    if (known_strings[4].find(a_candiate) == known_strings[4].npos) {
      mapping['a'] = a_candiate;
    }
  }
  // Solve for 9 string by matching with 4
  // 9 contains everything of 4, 0 and 6 do not
  for (const auto& str : inputs) {
    if (str.length() == 6) {
      if (are_all_chars_contained(str, known_strings.at(4))) {
        known_strings[9] = str;
      } else if (are_all_chars_contained(str, known_strings.at(7))) {
        known_strings[0] = str;
      } else {
        known_strings[6] = str;
      }
    }
  }
  remove_existing_elements();
  // Find the maping for d from zero
  // Find the maping for c from six
  // Find the maping for e from nine
  for (const auto& char_i : known_strings.at(8)) {
    const auto zero = known_strings.at(0);
    const auto six = known_strings.at(6);
    const auto nine = known_strings.at(9);
    if (zero.find(char_i) == zero.npos) {
      mapping['d'] = char_i;
    } else if (six.find(char_i) == six.npos) {
      mapping['c'] = char_i;
    } else if (nine.find(char_i) == nine.npos) {
      mapping['e'] = char_i;
    }
  }

  // Find the maping for f as the last char of 7 not know
  for (const auto& char_i : known_strings.at(7)) {
    if (char_i != mapping.at('a') && char_i != mapping.at('c')) {
      mapping['f'] = char_i;
      break;
    }
  }

  // Find 2 using e which is known
  for (const auto& str : inputs) {
    if (str.length() == 5) {
      if (str.find(mapping.at('e')) != str.npos) {
        known_strings[2] = str;
        break;
      }
    }
  }
  remove_existing_elements();

  // Only 3 and 5 are left
  // Find 3 based on it having c, the other is 5
  for (const auto& str : inputs) {
    if (str.find(mapping.at('c')) != str.npos) {
      known_strings[3] = str;
    } else {
      known_strings[5] = str;
    }
  }
  remove_existing_elements();
  // Confirm that all have been found
  if (inputs.size() != 0) {
    throw std::logic_error("Failed to find all strings");
  }

  // Now that all strings are know finish making the map
  // Find b from 3 and e
  for (const auto& char_i : known_strings.at(8)) {
    const auto three = known_strings.at(3);
    if ((three.find(char_i) == three.npos) && (char_i != mapping.at('e'))) {
      mapping['b'] = char_i;
      break;
    }
  }

  // Find the last remaining item
  {
    std::string eight = known_strings.at(8);
    std::string known;
    for (const auto& [key, item] : mapping) {
      known += item;
    }
    std::sort(eight.begin(), eight.end());
    std::sort(known.begin(), known.end());
    if (known.back() == eight.back()) {
      for (unsigned int i = 0; i < known.length(); i++) {
        if (known[i] != eight[i]) {
          mapping['g'] = eight[i];
          break;
        }
      }
    } else {
      mapping['g'] = eight.back();
    }
  }
  if (mapping.size() != 7) {
    throw std::logic_error("Failed to fill map");
  }
  return mapping;
}  // generate_conversion_map()

/**
 * @brief Determines if all the characters in check are in reference
 *
 * @param reference What the string is checked against
 * @param check string with expected chars
 * @return true All chars in check are in reference
 * @return false one of more chars from check are not in reference
 */
bool are_all_chars_contained(const std::string reference,
                             const std::string check) {
  for (const auto& char_i : check) {
    if (reference.find(char_i) == reference.npos) {
      return false;
    }
  }
  return true;
}  // are_all_chars_contained()

/**
 * @brief create a segment map from the conversion map
 *
 * @param conversion_map From generate_conversion_map()
 * @return std::map<std::string, int>
 */
std::map<std::string, int> generate_segment_map(
    const std::map<char, char> conversion_map) {
  std::map<std::string, int> segment_map;
  for (auto& map : standard_segment_map) {
    std::string key = map.first;
    for (auto& i : key) {
      i = conversion_map.at(i);
    }
    std::sort(key.begin(), key.end());
    segment_map.emplace(key, map.second);
  }
  return segment_map;
}  // generate_segment_map()