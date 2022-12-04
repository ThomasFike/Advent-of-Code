/**
 * @file day4.cpp
 */
#include <regex>

#include "common.hpp"

using Range = std::pair<int, int>;
using Assignment = std::pair<Range, Range>;

static Assignment get_pair(std::ifstream& file);
static bool is_enclosed(const Assignment& pair);
static bool is_overlap(const Assignment& pair);

int main() {
  std::ifstream file("small.txt");
  auto enclosed_total = 0;
  auto overlap_total = 0;
  while (file.good()) {
    const auto assignment = get_pair(file);
    if (is_enclosed(assignment)) {
      enclosed_total++;
    }
    if (is_overlap(assignment)) {
      overlap_total++;
    }
  }
  fmt::print("Found {} to be enclosed\n", enclosed_total);
  fmt::print("Found {} to be overlapping\n", overlap_total);
}

static Assignment get_pair(std::ifstream& file) {
  std::regex pair_regex(R"_((\d+)-(\d+),(\d+)-(\d+))_");
  const auto line = get_line(file);
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

static bool is_overlap(const Assignment& pair) {
  const auto& first = pair.first;
  const auto& second = pair.second;
  if (first.first >= second.first && first.first <= second.second) {
    return true;
  } else if (first.second >= second.first && first.second <= second.second) {
    return true;
  } else if (second.first >= first.first && second.first <= first.second) {
    return true;
  } else if (second.second >= first.first && second.second <= first.second) {
    return true;
  }
  return false;
}