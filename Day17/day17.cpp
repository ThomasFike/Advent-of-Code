/**
 * @file day11.cpp
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

template <size_t Size>
struct Computer {
  Computer(const uint32_t aRa, const uint32_t aRb, const uint32_t aRc,
           const std::array<uint8_t, Size>&& aInstructions)
      : rA(aRa), rB(aRb), rC(aRc), instructions(std::move(aInstructions)) {}
  uint32_t pc = 0;
  uint32_t rA;
  uint32_t rB;
  uint32_t rC;
  std::array<uint8_t, Size> instructions;
  uint32_t getValueForCompound(const uint8_t comp) const {
    switch (comp) {
      case 0:
        return 0;
      case 1:
        return 1;
      case 2:
        return 2;
      case 3:
        return 3;

      case 4:
        return rA;
      case 5:
        return rB;
      case 6:
        return rC;

      default:
        return 1000;
    }
  }
  std::optional<uint32_t> Iterate() {
    // std::cout << "Iterate PC(" << pc << ")" << "rA: " << rA << ", rB: " << rB
    //           << ", rC: " << rC << std::endl;

    const auto opCode = instructions[pc];
    const auto literalArg = instructions[pc + 1];
    const auto compArg = getValueForCompound(literalArg);
    switch (opCode) {
      case 0:
        rA = rA / (1 << compArg);
        break;

      case 1:
        rB = rB ^ literalArg;
        break;

      case 2:
        rB = compArg % 8;
        break;

      case 3:
        if (rA != 0) {
          pc = literalArg;
          return {};
        }
        break;

      case 4:
        rB = rB ^ rC;
        break;

      case 5:
        pc += 2;
        return compArg % 8;
        break;

      case 6:
        rB = rA / (1 << compArg);
        break;

      case 7:
        rC = rA / (1 << compArg);
        break;

      default:
        std::cout << "Error Unknown op code" << std::endl;
        break;
    }
    pc += 2;
    return {};
  }
};

int main() {
  // auto comp = Computer(729, 0, 0, std::to_array<uint8_t>({0, 1, 5, 4, 3,
  // 0}));
  auto comp = Computer(
      41644071, 0, 0,
      std::to_array<uint8_t>({2, 4, 1, 2, 7, 5, 1, 7, 4, 4, 0, 3, 5, 5, 3, 0}));
  std::vector<uint32_t> output;
  while (comp.pc < comp.instructions.size()) {
    const auto foo = comp.Iterate();
    if (foo.has_value()) {
      output.emplace_back(foo.value());
    }
  }
  for (const auto& value : output) {
    std::cout << value << ',';
  }
  std::cout << std::endl;
}