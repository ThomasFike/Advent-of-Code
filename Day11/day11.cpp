/**
 * @file day11.cpp
 */

#include <fmt/ostream.h>

#include <regex>
#include <stack>

#include "common.hpp"

class Operation {
 public:
  explicit Operation(const std::string& line);
  template <typename T>
  T doOp(const T initVal) const;
  friend std::ostream& operator<<(std::ostream& out, const Operation& op);

 private:
  enum Op { MultVal, MultSelf, AddVal };
  Op op;
  int val;
};

class Monkey {
 public:
  explicit Monkey(std::ifstream& in);
  friend void printMonkey(const Monkey& monkey);
  void updateWorry(void);
  auto getInspectedCount(void) const { return inspectedCount; }
  size_t passTo(int val) const {
    if (val % divisor == 0) {
      return static_cast<size_t>(throwTo.first);
    } else {
      return static_cast<size_t>(throwTo.second);
    }
  }
  std::vector<int> items;

 private:
  std::optional<Operation> op;
  std::pair<int, int> throwTo;
  int divisor;
  int inspectedCount = 0;
};

std::ostream& operator<<(std::ostream& out, const Operation& op) {
  const std::map<Operation::Op, std::string_view> enumMap = {
      {Operation::Op::AddVal, "AddVal"},
      {Operation::Op::MultVal, "MultVal"},
      {Operation::Op::MultSelf, "MultSelf"}};
  fmt::print(out, "Operation: {} with val {}", enumMap.at(op.op), op.val);
  return out;
}

template <>
struct fmt::formatter<Operation> : ostream_formatter {};

void printMonkey(const Monkey& monkey) {
  fmt::print("Items: {}\n", monkey.items);
  fmt::print("{}\n", monkey.op.value());
  fmt::print("Divisor: {}, Throw To: {}\n", monkey.divisor, monkey.throwTo);
}

void doRound(std::vector<Monkey>& monkeys);
int main() {
  std::ifstream inFile("part1.txt");
  std::vector<Monkey> monkeys;
  while (inFile.good()) {
    monkeys.emplace_back(Monkey(inFile));
  }
  for (int i = 1; i <= 20; i++) {
    fmt::print("Round {}\n", i);
    doRound(monkeys);
  }
  for (size_t i = 0; i < monkeys.size(); i++) {
    fmt::print("Monkey {} inspected {} items\n", i,
               monkeys[i].getInspectedCount());
  }
  std::vector<int> counts;
  std::transform(monkeys.cbegin(), monkeys.cend(), std::back_inserter(counts),
                 [](const auto& monkey) { return monkey.getInspectedCount(); });
  std::sort(counts.begin(), counts.end(), std::greater<int>());
  const auto level = counts[0] * counts[1];
  fmt::print("Level of Monkey Business: {}\n", level);
}

void doRound(std::vector<Monkey>& monkeys) {
  for (size_t i = 0; i < monkeys.size(); i++) {
    monkeys[i].updateWorry();
    for (size_t j = 0; j < monkeys[i].items.size(); j++) {
      const auto item = monkeys[i].items[j];
      const auto passTo = monkeys[i].passTo(item);
      monkeys[passTo].items.emplace_back(item);
    }
    monkeys[i].items.clear();
  }
  for (size_t i = 0; i < monkeys.size(); i++) {
    fmt::print("Monkey {} has: {}\n", i, monkeys[i].items);
  }
}

Operation::Operation(const std::string& line) {
  const std::regex multValMatch(R"~(old \* (\d+))~");
  const std::regex multSelfMatch(R"~(old \* old)~");
  const std::regex addValMatch(R"~(old \+ (\d+))~");

  std::smatch match;
  if (std::regex_search(line, multSelfMatch)) {
    op = Op::MultSelf;
    val = 0;
  } else if (std::regex_search(line, match, multValMatch)) {
    op = Op::MultVal;
    val = std::stoi(match[1]);
  } else if (std::regex_search(line, match, addValMatch)) {
    op = Op::AddVal;
    val = std::stoi(match[1]);
  } else {
    throw std::logic_error("Failed to parse operation");
  }
}

template <typename T>
T Operation::doOp(const T initVal) const {
  switch (op) {
    case Op::AddVal:
      return initVal + val;
    case Op::MultSelf:
      return initVal * initVal;
    case Op::MultVal:
      return initVal * val;
  }
  return 0;
}

Monkey::Monkey(std::ifstream& in) {
  std::string line;
  auto discard = [&](void) {
    std::string discardLine = get_line(in);
    // fmt::print("Discard:{}\n", discardLine);
  };
  discard();

  line = get_line(in);
  auto iter = line.cbegin();
  std::smatch match;
  const std::regex numberMatch(R"~((\d+))~");
  while (std::regex_search(iter, line.cend(), match, numberMatch)) {
    iter = match.suffix().first;
    if (!match[1].str().empty()) {
      items.emplace_back(std::stoi(match[1]));
    }
  }

  line = get_line(in);
  op = Operation(line);

  auto getInt = [&]() {
    line = get_line(in);
    if (std::regex_search(line, match, numberMatch)) {
      return std::stoi(match[1]);
    } else {
      throw std::logic_error("Can't pase Divisor");
    }
  };
  divisor = getInt();
  throwTo.first = getInt();
  throwTo.second = getInt();
  discard();
}

void Monkey::updateWorry(void) {
  auto update = [&](int& item) {
    const auto opComplete = op.value().doOp(item);
    item = static_cast<int>(static_cast<double>(opComplete) / 3.0);
    inspectedCount++;
  };
  std::for_each(items.begin(), items.end(), update);
}