/**
 * @file day3.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

static const std::regex mulMatcher(R"~(mul\((\d{1,3}),(\d{1,3})\))~");

int main() {
  std::ifstream inputFile(FileName);
  std::string line;
  std::getline(inputFile, line, '\0');
  const auto answer = std::accumulate(
      std::sregex_iterator(line.begin(), line.end(), mulMatcher),
      std::sregex_iterator(), 0, [](const int init, const std::smatch& val) {
        if (val.size() != 3) {
          throw std::logic_error("You done goofed");
        }
        const auto a = std::stoi(val[1]);
        const auto b = std::stoi(val[2]);
        return init + (a * b);
      });
  std::cout << "Answer: " << answer << std::endl;
}