/**
 * @file day3.cpp
 */

#include <algorithm>
#include <expected>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

enum Allowed {
  Do,
  Dont,
};

using Ops = std::pair<int, int>;
using Founds = std::expected<int, Allowed>;

static const std::regex mulMatcher(
    R"~(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))~");

int main() {
  std::ifstream inputFile(FileName);
  std::string line;
  std::getline(inputFile, line, '\0');
  std::vector<Founds> matches;
  for (auto iter = std::sregex_iterator(line.begin(), line.end(), mulMatcher);
       iter != std::sregex_iterator(); iter++) {
    const std::smatch& match = *iter;
    if (match.size() != 3) {
      throw std::logic_error("Invalid size");
    }

    if (match[0] == "don't()") {
      matches.emplace_back(std::unexpected(Allowed::Dont));
    } else if (match[0] == "do()") {
      matches.emplace_back(std::unexpected(Allowed::Do));
    } else {
      const auto a = std::stoi(match[1]);
      const auto b = std::stoi(match[2]);
      matches.emplace_back(a * b);
    }
  }
  auto lastAllowed = Allowed::Do;
  int answer = 0;
  for (const auto& item : matches) {
    if (item && lastAllowed == Allowed::Do) {
      answer += item.value();
    } else {
      lastAllowed = item.error();
    }
  }
  std::cout << "Answer: " << answer << std::endl;
}