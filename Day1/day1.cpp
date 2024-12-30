/**
 * @file day1.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

int main() {
  std::ifstream inputFile(FileName);
  std::vector<int> list1;
  std::vector<int> list2;
  while (inputFile && !inputFile.eof()) {
    int temp1 = 0;
    int temp2 = 0;
    inputFile >> temp1 >> temp2;
    list1.emplace_back(temp1);
    list2.emplace_back(temp2);
  }

  std::ranges::sort(list1);
  std::ranges::sort(list2);
  int answer = 0;

  for (auto lIter = list1.cbegin(), rIter = list2.cbegin();
       lIter != list1.cend() && rIter != list2.cend();) {
    const auto value = *lIter;
    // std::cout << "Doing check for: " << value << std::endl;
    const auto isNotValue = [&](const auto aValue) { return value != aValue; };
    // See how many copies exist in left list
    const auto endOfLRange = std::find_if(lIter, list1.cend(), isNotValue);

    // Subtract 1 because it's one past the end
    const auto leftCount = std::distance(lIter, endOfLRange);

    // Move lIter
    lIter = endOfLRange;

    // Move rIter
    rIter = std::find_if(rIter, list2.cend(), [value](const auto aValue) {
      return aValue >= value;
    });

    if (rIter == list2.cend() || *rIter != value) {
      continue;
    }

    const auto endOfRRange = std::find_if(rIter, list2.cend(), isNotValue);
    const auto rightCount = std::distance(rIter, endOfRRange);

    // Move rIter
    rIter = endOfRRange;

    // Incrent answer
    // std::cout << "Left: " << leftCount << ", Right: " << rightCount
    //           << std::endl;
    answer += leftCount * rightCount * value;
  }
  std::cout << "Answer: " << answer << std::endl;
}