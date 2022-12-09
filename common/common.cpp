/**
 * @file common.cpp
 */

#include "common.hpp"

/**
 * @brief Get a line from a file
 *
 * @param in_file ifstream
 * @return std::string
 */
std::string get_line(std::ifstream& in_file) {
  std::string line;
  std::getline(in_file, line);
  return line;
}

/**
 * @brief Convert a single number as a char to it's int
 *
 * @param letter
 * @return int
 */
int convertCharToInt(const char letter) {
  switch (letter) {
    case '9':
      return 9;
      break;
    case '8':
      return 8;
      break;
    case '7':
      return 7;
      break;
    case '6':
      return 6;
      break;
    case '5':
      return 5;
      break;
    case '4':
      return 4;
      break;
    case '3':
      return 3;
      break;
    case '2':
      return 2;
      break;
    case '1':
      return 1;
      break;
    default:
      fmt::print("Unknown Letter [{}]", letter);
    case '0':
      return 0;
      break;
  }
}