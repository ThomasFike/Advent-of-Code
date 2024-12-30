/**
 * @file day5.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

struct Rule {
  Rule() : mFirstPage(0), mSecondPage(0) {}
  Rule(const int aFirstPage, const int aSecondPage)
      : mFirstPage(aFirstPage), mSecondPage(aSecondPage) {}
  int mFirstPage;
  int mSecondPage;
};

static std::optional<std::vector<int>> FixOrderIfInvalid(
    const std::vector<Rule>& rules, const std::vector<int>& order) {
  std::cout << std::endl;
  auto applying_rules =
      rules | std::views::transform([&](const Rule& rule) {
        std::pair<std::optional<int>, std::optional<int>> indexes;
        for (const auto& [index, page] : std::views::enumerate(order)) {
          if (rule.mFirstPage == page) {
            indexes.first = index;
          } else if (rule.mSecondPage == page) {
            indexes.second = index;
          }
          if (indexes.first.has_value() && indexes.second.has_value()) {
            break;
          }
        }
        return indexes;
      }) |
      std::ranges::views::filter(
          [](const std::pair<std::optional<int>, std::optional<int>>& rule) {
            return rule.first.has_value() && rule.second.has_value();
          });

  auto violating_rules =
      applying_rules |
      std::ranges::views::filter(
          [](const std::pair<std::optional<int>, std::optional<int>>& rule) {
            return rule.first.value() > rule.second.value();
          });
  std::vector invalidRecords(violating_rules.begin(), violating_rules.end());
  if (invalidRecords.size() == 0) {
    return {};
  }
  auto mutOrder = order;
  std::sort(
      mutOrder.begin(), mutOrder.end(), [&](const int lhs, const int rhs) {
        const auto rule =
            std::find_if(rules.begin(), rules.end(), [&](const Rule& aRule) {
              return (aRule.mFirstPage == lhs || aRule.mSecondPage == lhs) &&
                     (aRule.mFirstPage == rhs || aRule.mSecondPage == rhs);
            });
        if (rule == rules.end()) {
          return false;
        }
        return lhs == rule->mFirstPage;
      });
  return mutOrder;
}

int main() {
  std::ifstream inputFile(FileName);
  std::vector<Rule> rules;
  std::vector<std::vector<int>> printOrders;
  std::string line;
  getline(inputFile, line);
  // Get First Part
  do {
    const auto pipeIdx = line.find('|');
    std::string second = line.substr(pipeIdx + 1);
    try {
      rules.emplace_back(std::stoi(line), std::stoi(second));
    } catch (std::invalid_argument& e) {
      std::cout << "Failure with line=" << line << std::endl;
    }
  } while (getline(inputFile, line).good() && !line.empty());

  // Get Second Part
  while (inputFile.good()) {
    getline(inputFile, line);
    std::vector<int> order;
    for (char const* str = line.c_str(); str < line.c_str() + line.size();) {
      char* foundEnd = nullptr;
      const auto val = std::strtol(str, &foundEnd, 10);
      str = foundEnd + 1;
      order.emplace_back(val);
    }
    printOrders.emplace_back(std::move(order));
  }

  auto validOrderMiddles =
      printOrders | std::ranges::views::transform([&](const auto& aOrder) {
        return FixOrderIfInvalid(rules, aOrder);
      }) |
      std::ranges::views::filter(
          [](const auto& aOrder) { return aOrder.has_value(); }) |
      std::ranges::views::transform([](const auto& aOrder) {
        return aOrder.value()[aOrder.value().size() / 2];
      });

  const auto answer =
      std::ranges::fold_left(validOrderMiddles, 0, std::plus<int>());
  std::cout << "Answer: " << answer << std::endl;
}