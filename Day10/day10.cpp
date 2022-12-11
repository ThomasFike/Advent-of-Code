/**
 * @file day10.cpp
 */

#include <fmt/ostream.h>

#include <list>
#include <regex>

#include "common.hpp"

class CPU {
 public:
  enum Instruction { Noop, Add };
  void addOp(const Instruction op, const long val);
  void doCycle(void);
  auto getCycle(void) const { return cycle; }
  auto getScore(void) const { return score; }
  bool hasWork(void) const { return !pending.empty(); }

 private:
  struct AddInstruct {
    int countLeft = 2;
    long val;
  };
  unsigned int cycle = 0;
  long X = 1;
  long score = 0;
  std::list<std::pair<Instruction, AddInstruct>> pending;
  void handleScore(void);
};

void CPU::doCycle(void) {
  if (pending.empty()) {
    return;
  }
  cycle++;
  handleScore();
  auto& [inst, addInfo] = pending.front();
  switch (inst) {
    case Instruction::Add:
      addInfo.countLeft--;
      if (addInfo.countLeft == 0) {
        X += addInfo.val;
        pending.pop_front();
      }
      break;
    case Instruction::Noop:
      pending.pop_front();
      break;
  }

  // fmt::print("Cycle: {}, X={}\n", cycle, X);
}

void CPU::addOp(const Instruction op, const long val) {
  AddInstruct instruct;
  if (op == Instruction::Add) {
    instruct.val = val;
  }
  pending.push_back({op, instruct});
}

void CPU::handleScore(void) {
  if (cycle >= 20 && cycle <= 220 && ((cycle - 20) % 40 == 0)) {
    const auto newScore = cycle * X;
    score += newScore;
    // fmt::print("Adding Score ({} x {}) = {}\nProduced: {}\n", cycle, X,
    //            newScore, score);
  }
}

std::pair<CPU::Instruction, long> parseLine(const std::string& line) {
  const std::regex noopMatch(R"~(noop)~");
  const std::regex addxMatch(R"~(addx ([-\d]+))~");

  std::smatch match;
  if (std::regex_match(line, noopMatch)) {
    return {CPU::Instruction::Noop, 0};
  } else if (std::regex_search(line, match, addxMatch)) {
    return {CPU::Instruction::Add, std::stol(match.str(1))};
  } else {
    // throw std::logic_error("Could not parse");
    return {CPU::Instruction::Noop, 0};
  }
}

int main() {
  std::ifstream inFile("part1.txt");
  CPU myCpu;
  while (inFile.good()) {
    const auto line = get_line(inFile);
    const auto [op, val] = parseLine(line);
    myCpu.addOp(op, val);
    myCpu.doCycle();
  }
  while (myCpu.hasWork()) {
    myCpu.doCycle();
  }
  fmt::print("Score: {}\n", myCpu.getScore());
}
