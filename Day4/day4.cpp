/**
 * @file day4.cpp
 */

#include <algorithm>
// #include <expected>
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

  const auto findMatches = [&](const Posn startPosn,
                               const char searchChar) -> std::vector<Posn> {
    const auto initalRow = startPosn.row > 0 ? startPosn.row - 1 : 0;
    const auto initialCol = startPosn.col > 0 ? startPosn.col - 1 : 0;

    std::vector<Posn> positions;
    for (size_t row = initalRow;
         row <= startPosn.row + 1 && row < puzzle.size(); row++) {
      for (size_t col = initialCol;
           col <= startPosn.col + 1 && col < puzzle[row].size(); col++) {
        // std::cout << "Checking: " << row << "," << col << std::endl;
        if (puzzle[row][col] == searchChar) {
          positions.emplace_back(row, col);
        }
      }
    }
    return positions;
  };

  int count = 0;
  for (size_t xRow = 0; xRow < puzzle.size(); xRow++) {
    for (size_t xCol = 0; xCol < puzzle[xRow].size(); xCol++) {
      if (puzzle[xRow][xCol] != 'X') {
        continue;
      }
      // Find all 'M's
      const auto mPosns = findMatches(Posn(xRow, xCol), 'M');
      for (const auto& mPosn : mPosns) {
        int rowOffset = mPosn.row - xRow;
        int colOffset = mPosn.col - xCol;
        // Bounds check
        if ((rowOffset < 0 && xRow < 3) ||
            (rowOffset > 0 && xRow + 3 >= puzzle.size()) ||
            (colOffset < 0 && xCol < 3) ||
            (colOffset > 0 && xCol + 3 >= puzzle[0].size())) {
          continue;
        }
        if (puzzle[xRow + (rowOffset * 2)][xCol + (colOffset * 2)] == 'A' &&
            puzzle[xRow + (rowOffset * 3)][xCol + (colOffset * 3)] == 'S') {
                  count++;
        }
      }
    }
  }

  std::cout << "Answer: " << count << std::endl;
}