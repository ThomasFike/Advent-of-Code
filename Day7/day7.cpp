/**
 * @file day6.cpp
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

struct Row {
  uint64_t mResult;
  std::vector<uint64_t> mOptions;

  bool IsPossible() const {
    const auto options = GetOptions();
    return std::any_of(
        options.cbegin(), options.cend(),
        [this](const auto& aVal) { return IsValidOption(aVal); });
  }

 private:
  using Operations = std::vector<std::function<uint64_t(uint64_t, uint64_t)>>;
  std::vector<Operations> GetOptions() const {
    const auto itemCount = mOptions.size();
    std::vector<Operations> options;
    for (size_t i = 0; i <= (1U << itemCount); i++) {
      Operations row;
      for (size_t j = 0; j < itemCount; j++) {
        if (i & (1 << j)) {
          row.emplace_back(std::plus<uint64_t>());
        } else {
          row.emplace_back(std::multiplies<uint64_t>());
        }
      }
      options.emplace_back(row);
    }
    return options;
  }

  bool IsValidOption(const Operations& aOperations) const {
    uint64_t sum = mOptions[0];
    for (size_t i = 0; i < mOptions.size(); i++) {
      sum = aOperations[i](sum, mOptions[i + 1]);
      if (sum > mResult) {
        return false;
      }
    }
    return sum == mResult;
  }
};

int main() {
  std::ifstream inputFile(FileName);
  std::vector<Row> rows;
  while (inputFile.good()) {
    std::string line;
    getline(inputFile, line);
    size_t posn;

    Row row{std::stoull(line, &posn), {}};

    for (char const* str = line.c_str() + posn + 1;
         str < line.c_str() + line.size();) {
      char* foundEnd = nullptr;
      const auto val = std::strtoull(str, &foundEnd, 10);
      str = foundEnd + 1;
      row.mOptions.push_back(val);
    }
    rows.emplace_back(std::move(row));
  }
  std::cout << "Got input" << std::endl;

  auto foo = rows | std::views::transform(
                        [](const Row& row) { return row.mOptions.size(); });

  const auto maxCount = std::max_element(foo.begin(), foo.end());

  std::cout << "Max Count: " << *maxCount << std::endl;

  const auto answer =
      std::accumulate(rows.cbegin(), rows.cend(), static_cast<uint64_t>(0),
                      [](const uint64_t aAccum, const Row& aRow) {
                        if (aRow.IsPossible()) {
                          return aAccum + aRow.mResult;
                        } else {
                          return aAccum;
                        }
                      });
  std::cout << "Answer: " << answer << std::endl;
}