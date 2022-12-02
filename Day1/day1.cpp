/**
 * @file day1.cpp
 */
#include "common.hpp"

std::vector<std::vector<int>> read_elf_list(std::ifstream& in);

int main() {
  std::ifstream in_file("part1.txt");
  auto elves = read_elf_list(in_file);
  std::vector<int> totals;
  std::transform(elves.begin(), elves.end(), std::back_inserter(totals),
                 [](std::vector<int> calories) {
                   return std::accumulate(calories.begin(), calories.end(), 0);
                 });
  const auto max_idx = std::distance(
      totals.begin(), std::max_element(totals.begin(), totals.end()));
  std::cout << "Elf with Most " << max_idx + 1 << " With "
            << totals[static_cast<unsigned long>(max_idx)] << " Calories"
            << std::endl;

  std::sort(totals.begin(), totals.end(),
            [](const auto& a, const auto& b) { return a > b; });
  int total = 0;
  for (size_t i = 0; i < 3; i++) {
    total += totals[i];
  }
  std::cout << "Top 3 Total: " << total << std::endl;
}

std::vector<std::vector<int>> read_elf_list(std::ifstream& in) {
  int read;
  std::vector<std::vector<int>> elfs;
  while (in.good()) {
    char throw_away;
    std::vector<int> one_elf;
    while (in.good()) {
      if (in.peek() == '\n' && in.read(&throw_away, 1) && in.peek() == '\n') {
        break;
      }
      in >> read;
      one_elf.emplace_back(read);
    }
    elfs.emplace_back(one_elf);
  }
  return elfs;
}