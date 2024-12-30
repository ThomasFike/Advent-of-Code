/**
 * @file day2.cpp
 */

#include <algorithm>
#include <expected>
#include <fstream>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

static std::expected<void, size_t> isSafeOnce(const auto& aRow) {
  const bool isAscending = aRow[1] > aRow[0];

  for (size_t i = 0; i < aRow.size() - 1; i++) {
    if (aRow.size() < 2) {
      throw std::logic_error("Invalid");
    }
    const bool pairIsAscending = aRow[i + 1] > aRow[i];
    const auto delta = std::abs(aRow[i + 1] - aRow[i]);
    if (isAscending != pairIsAscending || (delta <= 0 || delta > 3)) {
      return std::unexpected(i);
    }
  }
  return {};
}

static bool isSafeWithRemoveBrutForce(const auto& aRow) {
  const auto isSafeFirst = isSafeOnce(aRow);
  if (isSafeFirst) {
    return true;
  }
  for (size_t i = 0; i < aRow.size(); i++) {
    std::vector temp = aRow;
    temp.erase(temp.begin() + i);
    if (isSafeOnce(temp)) {
      return true;
    }
  }
  return false;
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
      std::count_if(rows.begin(), rows.end(),
                    [](auto& aRow) { return isSafeWithRemoveBrutForce(aRow); });
  std::cout << "Safe Count: " << safeCount << std::endl;
}