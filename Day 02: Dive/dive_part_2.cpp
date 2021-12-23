/*
 * @file dive_part_2.cpp
 * @author Thomas Fike
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

enum class DIRECTION { UP, DOWN, FORWARD, INVALID };

[[nodiscard]] static const std::pair<DIRECTION, int> convert_string(
    std::string input_string);
[[nodiscard]] static std::string get_string_from_istream(std::istream& input);

int main() {
  std::ifstream input_file("input.txt");
  int depth = 0;
  int distance = 0;
  int aim = 0;
  while (input_file.good()) {
    const std::string current_line = get_string_from_istream(input_file);
    const auto [action, amount] = convert_string(current_line);
    switch (action) {
      case DIRECTION::UP:
        aim -= amount;
        break;
      case DIRECTION::DOWN:
        aim += amount;
        break;
      case DIRECTION::FORWARD:
        distance += amount;
        depth += (amount * aim);
        break;
      case DIRECTION::INVALID:
      default:
        break;
    }
  }

  std::cout << "Depth, Distance: " << depth << ", " << distance << std::endl;
  std::cout << "Depth * Distance: " << (depth * distance) << std::endl;

  input_file.close();
}

[[nodiscard]] static const std::pair<DIRECTION, int> convert_string(
    std::string input_string) {
  DIRECTION dir = DIRECTION::INVALID;
  int amount = 0;

  std::stringstream input_stream(input_string);
  std::string action;
  getline(input_stream, action, ' ');
  for (auto& i : action) {
    i = tolower(i);
  }
  if (action == "forward") {
    dir = DIRECTION::FORWARD;
  } else if (action == "up") {
    dir = DIRECTION::UP;
  } else if (action == "down") {
    dir = DIRECTION::DOWN;
  }
  input_stream >> amount;
  return {dir, amount};
}

[[nodiscard]] static std::string get_string_from_istream(std::istream& input) {
  std::string temp;
  getline(input, temp);
  return temp;
}