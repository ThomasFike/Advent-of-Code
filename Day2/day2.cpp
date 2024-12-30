/**
 * @file day2.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

static bool isSafe(const std::vector<int> aRow) {
  if (aRow.size() < 2) {
    return false;
  }
  const bool isAscending = aRow[1] > aRow[0];
  for (size_t i = 0; i < aRow.size() - 1; i++) {
    const bool pairIsAscending = aRow[i + 1] > aRow[i];
    if (isAscending != pairIsAscending) {
      return false;
    }
    const auto delta = std::abs(aRow[i + 1] - aRow[i]);
    if (delta <= 0 || delta > 3) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ifstream inputFile(FileName);
  std::vector<std::vector<int>> rows;
  while (inputFile.good()) {
    rows.emplace_back();
    auto& row = rows.back();
    std::string line;
    std::getline(inputFile, line);
    for (size_t i = 0; i < line.size(); i++) {
      const auto nextSpace = line.find_first_of(' ', i);
      row.emplace_back(std::strtol(line.c_str() + i, nullptr, 10));
      i = nextSpace;
      if (i == std::string::npos) {
        i = line.size();
      }
    }
  }
  // for (const auto& row : rows) {
  //   for (const auto& item : row) {
  //     std::cout << item << ' ';
  //   }
  //   std::cout << std::endl;
  // }
  const auto safeCount =
      std::count_if(rows.cbegin(), rows.cend(),
                    [](const auto& aRow) { return isSafe(aRow); });
  std::cout << "Safe Count: " << safeCount << std::endl;
}