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