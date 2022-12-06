/**
 * @file day5.cpp
 */
#include <fmt/ostream.h>

#include <regex>

#include "common.hpp"

struct Instruction {
  size_t count = 0;
  size_t from = 0;
  size_t to = 0;
  friend std::ostream& operator<<(std::ostream& out, const Instruction& ins) {
    fmt::print(out, "Count: {} From: {} To: {}", ins.count, ins.from, ins.to);

    return out;
  }
};

template <>
struct fmt::formatter<Instruction> : ostream_formatter {};

static std::vector<std::stack<char>> getStartingStacks(std::ifstream& inFile);
static std::optional<Instruction> readInstruction(std::ifstream& inFile);

int main() {
  std::ifstream inFile("part1.txt");
  auto stacks = getStartingStacks(inFile);
  do {
    auto instruct = readInstruction(inFile).value();
    auto& from = stacks[instruct.from - 1];
    auto& to = stacks[instruct.to - 1];
    while (instruct.count && from.size()) {
      const auto item = from.top();
      from.pop();
      to.push(item);
      instruct.count--;
    }
  } while (inFile.good());
  std::string outString;
  std::transform(stacks.begin(), stacks.end(), std::back_inserter(outString),
                 [](const auto& item) { return item.top(); });
  fmt::print("Out: {}\n", outString);
}

static std::vector<std::stack<char>> getStartingStacks(std::ifstream& inFile) {
  // Read in whole top starting part
  std::vector<std::string> startingStacksString;
  do {
    startingStacksString.emplace_back(get_line(inFile));
  } while (inFile.good() && startingStacksString.back() != "");
  startingStacksString.pop_back();
  std::smatch match;
  size_t stackCount = 0;
  if (std::regex_search(startingStacksString.back(), match,
                        std::regex("(\\d+)\\s*$"))) {
    stackCount = std::stoul(match[1]);
  } else {
    fmt::print("Could not match stack count");
  }
  startingStacksString.pop_back();

  std::vector<std::stack<char>> stacks(stackCount);
  std::regex item_regex(R"_(\[(\w)\]|\s{4})_");
  // Run lines bottom to top and then iterating across each line adding matches
  std::for_each(
      startingStacksString.rbegin(), startingStacksString.rend(),
      [&](const auto& str) {
        size_t idx = 0;
        auto iter = str.begin();
        while (std::regex_search(iter, str.end(), match, item_regex)) {
          iter = match.suffix().first;
          if (!match[1].str().empty()) {
            stacks[idx].push(match[1].str()[0]);
          }
          idx++;
        }
      });
  return stacks;
}

static std::optional<Instruction> readInstruction(std::ifstream& inFile) {
  std::regex instruction_regex(R"_(move (\d+) from (\d+) to (\d+))_");
  const std::string line = get_line(inFile);
  std::smatch match;
  if (std::regex_search(line, match, instruction_regex)) {
    Instruction instruction;
    instruction.count = std::stoul(match[1]);
    instruction.from = std::stoul(match[2]);
    instruction.to = std::stoul(match[3]);
    return instruction;
  } else {
    return {};
  }
}