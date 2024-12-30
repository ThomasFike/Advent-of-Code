/**
 * @file day1.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

static const auto FileName = "small.txt";

int main() {
  std::ifstream inputFile(FileName);
  std::vector<int> list1;
  std::vector<int> list2;
  while (inputFile) {
    int temp1;
    int temp2;
    inputFile >> temp1 >> temp2;
    list1.emplace_back(temp1);
    list2.emplace_back(temp2);
  }
  std::cout << "read done" << std::endl;
  for (size_t i; i < list1.size(); i++) {
    std::cout << '(' << list1.at(i) << ',' << list2.at(i) << ")\r\n";
  }

  std::cout << "after sort" << std::endl;

  std::ranges::sort(list1);
  std::ranges::sort(list2);
  std::ranges::zip_view view(list1, list2);
  auto values = view | std::ranges::views::transform([](auto aTuple) {
                  return std::abs(std::get<1>(aTuple) - std::get<0>(aTuple));
                });
  const auto value = std::ranges::fold_left(values, 0, std::plus<int>());
  std::cout << "Answer: " << value << std::endl;
}