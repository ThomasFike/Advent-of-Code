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
    std::string line;
    std::getline(in, line);
    PACKS packs;
    std::copy(line.begin(), line.begin() + static_cast<int>(line.length() / 2),
              std::back_inserter(packs.first));
    std::copy(line.begin() + static_cast<int>(line.length() / 2), line.end(),
              std::back_inserter(packs.second));
    auto remove_duplicates = [](std::vector<char>& list) {
      std::sort(list.begin(), list.end());
      list.erase(std::unique(list.begin(), list.end()), list.end());
    };
    remove_duplicates(packs.first);
    remove_duplicates(packs.second);
    std::vector<char> matches;
    std::set_intersection(packs.first.begin(), packs.first.end(),
                          packs.second.begin(), packs.second.end(),
                          std::back_inserter(matches));
    if (matches.size() == 0) {
      std::cout << "No Match";
    } else {
      const auto priority = get_priority(matches[0]);
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