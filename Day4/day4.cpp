/**
 * @file day4.cpp
 */
#include <regex>

#include "common.hpp"

using Range = std::pair<int, int>;
using Assignment = std::pair<Range, Range>;

static Assignment get_pair(std::ifstream& file);
static bool is_enclosed(const Assignment& pair);

int main() {
  std::ifstream file("part1.txt");
  auto total = 0;
  while (file.good()) {
    const auto assignment = get_pair(file);
    if (is_enclosed(assignment)) {
      total++;
    }
  }
  std::cout << "Found " << total << " to be enclosed" << std::endl;
}

static Assignment get_pair(std::ifstream& file) {
  std::regex pair_regex(R"_((\d+)-(\d+),(\d+)-(\d+))_");
  std::string line;
  std::getline(file, line);
  std::smatch matches;
  Assignment pair;
  if (std::regex_search(line, matches, pair_regex) && matches.size() == 5) {
    pair.first.first = std::stoi(matches[1]);
    pair.first.second = std::stoi(matches[2]);
    pair.second.first = std::stoi(matches[3]);
    pair.second.second = std::stoi(matches[4]);
  } else {
    throw;
  }
  return pair;
}

static bool is_enclosed(const Assignment& pair) {
  const auto& first = pair.first;
  const auto& second = pair.second;
  // Check for first in second
  if (second.first <= first.first && first.second <= second.second) {
    return true;
  }
  // Check for second in first
  if (first.first <= second.first && second.second <= first.second) {
    return true;
  }
  return false;
}