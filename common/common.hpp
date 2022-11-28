/**
 * @file common.hpp
 */

#ifndef COMMON_HPP
#define COMMON_HPP

/**
 * @section Common Includes
 */
#include <fstream>
#include <iomanip>
#include <iostream>
/// Containers
#include <array>
#include <vector>
/// Counting
#include <algorithm>
#include <numeric>

/**
 * @brief Prints out the contents of a vector as a comma seperated list
 *
 * @bug If the last element is the same as any number of the last elements there
 * will be no commas
 * @tparam T
 * @param vec vector to be printed
 */
template <typename T>
void print_vector(std::vector<T> vec) {
  for (const auto& i : vec) {
    std::cout << i;
    if (i != vec.back()) {
      std::cout << ',';
    }
  }
  std::cout << std::endl;
}

/**
 * @brief Reads in a file that contains comma separated values into a vector
 *
 * @tparam T
 * @return std::vector<T>
 */
template <typename T>
std::vector<T> read_comma_separated_file(std::istream& input) {
  std::vector<T> values;
  while (input.good()) {
    char throw_away_char;
    T temp;
    input >> temp >> throw_away_char;
    values.emplace_back(temp);
  }
  return values;
}
#endif