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

  std::ranges::zip_view view(list1, list2);
  auto values = view | std::ranges::views::transform([](auto aTuple) {
                  return std::abs(std::get<1>(aTuple) - std::get<0>(aTuple));
                });
  const auto value = std::ranges::fold_left(values, 0, std::plus<int>());
  std::cout << "Answer: " << value << std::endl;
}