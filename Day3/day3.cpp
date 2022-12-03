/**
 * @file day3.cpp
 */
#include "common.hpp"

using PACKS = std::pair<std::vector<char>, std::vector<char>>;

static int get_priority(const char& match);

int main() {
  std::ifstream in("part1.txt");
  if (!in.is_open()) {
    return 0;
  }
  int total = 0;
  while (in.good()) {
    std::array<std::vector<char>, 3> lines;
    std::generate(lines.begin(), lines.end(), [&]() {
      std::string line;
      std::vector<char> chars;
      std::getline(in, line);
      std::copy(line.begin(), line.end(), std::back_inserter(chars));
      return chars;
    });
    auto remove_duplicates = [](std::vector<char>& list) {
      std::sort(list.begin(), list.end());
      list.erase(std::unique(list.begin(), list.end()), list.end());
    };
    std::for_each(lines.begin(), lines.end(), remove_duplicates);
    std::vector<char> first_matches;
    std::set_intersection(lines[0].begin(), lines[0].end(), lines[1].begin(),
                          lines[1].end(), std::back_inserter(first_matches));
    std::vector<char> second_matches;
    std::set_intersection(first_matches.begin(), first_matches.end(),
                          lines[2].begin(), lines[2].end(),
                          std::back_inserter(second_matches));
    if (second_matches.size() == 0) {
      std::cout << "No Match";
    } else {
      const auto priority = get_priority(second_matches[0]);
      std::cout << priority << std::endl;
      total += priority;
    }
  }
  std::cout << "Total: " << total << std::endl;
}

static int get_priority(const char& match) {
  if (match >= 'A' && match <= 'Z') {
    return static_cast<int>(match) - static_cast<int>('A') + 27;
  } else {
    return static_cast<int>(match) - static_cast<int>('a') + 1;
  }
}