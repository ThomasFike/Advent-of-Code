/**
 * @file day4.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

struct Posn {
  Posn(size_t aRow, size_t aCol) : row(aRow), col(aCol) {}
  size_t row;
  size_t col;
};

int main() {
  std::ifstream inputFile(FileName);
  std::vector<std::string> puzzle;
  while (inputFile.good()) {
    puzzle.emplace_back();
    std::getline(inputFile, puzzle.back());
  }

  int count = 0;
  for (size_t aRow = 1; aRow < puzzle.size() - 1; aRow++) {
    for (size_t aCol = 1; aCol < puzzle[aRow].size() - 1; aCol++) {
      if (puzzle[aRow][aCol] != 'A') {
        continue;
      }
      const auto ul = puzzle[aRow - 1][aCol - 1];
      const auto ur = puzzle[aRow - 1][aCol + 1];
      const auto ll = puzzle[aRow + 1][aCol - 1];
      const auto lr = puzzle[aRow + 1][aCol + 1];

      const auto isMOrS = [](const char aChar) {
        return aChar == 'M' || aChar == 'S';
      };
      const auto getOpposite = [](const char aChar) {
        return aChar == 'M' ? 'S' : 'M';
      };

      if (!isMOrS(ul) || !isMOrS(ur) || !isMOrS(ll) || !isMOrS(lr)) {
        continue;
      }
      if (getOpposite(ur) != ll) {
        continue;
      }
      if (getOpposite(ul) != lr) {
        continue;
      }
      count++;
    }
  }

  std::cout << "Answer: " << count << std::endl;
}