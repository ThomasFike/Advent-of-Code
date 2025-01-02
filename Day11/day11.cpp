/**
 * @file day11.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>
#include <set>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

using StoneType = uint64_t;
using Stones = std::vector<StoneType>;

int main() {
  std::ifstream inputFile(FileName);
  Stones stones;

  while (inputFile.good()) {
    std::string line;
    getline(inputFile, line);

    for (char const* str = line.c_str(); str < line.c_str() + line.size();) {
      char* foundEnd = nullptr;
      const auto val = std::strtoull(str, &foundEnd, 10);
      str = foundEnd + 1;
      stones.push_back(val);
    }
  }
  for (const auto& stone : stones) {
    std::cout << stone << " ";
  }
  std::cout << std::endl;
  static constexpr size_t BlinkCount = 25;

  for (size_t blinkIdx = 0; blinkIdx < BlinkCount; blinkIdx++) {
    for (size_t idx = 0; idx < stones.size(); idx++) {
      auto& stone = stones[idx];
      const auto previousValue = stone;
      const auto valueString = std::to_string(previousValue);
      if (previousValue == 0) {
        stone = 1;
      } else if (valueString.size() % 2 == 0) {
        const auto oldStoneString =
            valueString.substr(0, valueString.size() / 2);
        const auto newStoneString = valueString.substr(valueString.size() / 2);

        const auto oldStoneValue = std::stoull(oldStoneString);
        const auto newStoneValue = std::stoull(newStoneString);

        stone = oldStoneValue;
        stones.insert(stones.begin() + idx + 1, newStoneValue);
        idx++;
      } else {
        stone *= 2024;
      }
    }
    // std::cout << "After blink " << blinkIdx + 1 << std::endl;
    // for (const auto& stone : stones) {
    //   std::cout << stone << " ";
    // }
    // std::cout << std::endl;
  }

  std::cout << "Answer: " << stones.size() << std::endl;
}