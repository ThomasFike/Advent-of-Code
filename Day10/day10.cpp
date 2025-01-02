/**
 * @file day10.cpp
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

int convertCharToInt(const char letter) {
  switch (letter) {
    case '9':
      return 9;
      break;
    case '8':
      return 8;
      break;
    case '7':
      return 7;
      break;
    case '6':
      return 6;
      break;
    case '5':
      return 5;
      break;
    case '4':
      return 4;
      break;
    case '3':
      return 3;
      break;
    case '2':
      return 2;
      break;
    case '1':
      return 1;
      break;
    default:
    case '0':
      return 0;
      break;
  }
}

struct Posn {
  Posn(size_t aRow, size_t aCol) : mRow(aRow), mCol(aCol) {}
  size_t mRow;
  size_t mCol;
};

using Puzzle = std::vector<std::string>;

static std::vector<Posn> findNextPossiblePaths(const Puzzle& aPuzzle,
                                               const Posn aCurrentPosition) {
  const auto startRow = aCurrentPosition.mRow;
  const auto startCol = aCurrentPosition.mCol;
  const auto requiredElevation = aPuzzle[startRow][startCol] + 1;
  std::vector<Posn> nextPositions;

  if (startRow > 0 && aPuzzle[startRow - 1][startCol] == requiredElevation) {
    nextPositions.emplace_back(startRow - 1, startCol);
  }
  if (startRow < aPuzzle.size() - 1 &&
      aPuzzle[startRow + 1][startCol] == requiredElevation) {
    nextPositions.emplace_back(startRow + 1, startCol);
  }
  if (startCol > 0 && aPuzzle[startRow][startCol - 1] == requiredElevation) {
    nextPositions.emplace_back(startRow, startCol - 1);
  }
  if (startCol < aPuzzle[0].size() - 1 &&
      aPuzzle[startRow][startCol + 1] == requiredElevation) {
    nextPositions.emplace_back(startRow, startCol + 1);
  }

  return nextPositions;
}

static int getSummits(const Puzzle& aPuzzle, const Posn& aCurrentPosition) {
  const auto locationElevation =
      aPuzzle[aCurrentPosition.mRow][aCurrentPosition.mCol];
  // std::cout << "Doing at (" << aCurrentPosition.mRow << ','
  //           << aCurrentPosition.mCol << ") of value " << locationElevation
  //           << std::endl;
  if (locationElevation == '9') {
    // std::cout << "Found" << std::endl;
    return 1;
  }
  const auto next = findNextPossiblePaths(aPuzzle, aCurrentPosition);
  if (next.size() == 0) {
    return 0;
  }
  int value = 0;
  for (const auto& nextPos : next) {
    value += getSummits(aPuzzle, nextPos);
  }
  return value;
}

int main() {
  std::ifstream inputFile(FileName);
  Puzzle puzzle;

  while (inputFile.good()) {
    std::string line;
    std::getline(inputFile, line);
    puzzle.emplace_back(line);
  }
  int answer = 0;
  for (const auto& [rowIndex, row] : std::views::enumerate(puzzle)) {
    for (const auto& [colIndex, col] : std::views::enumerate(row)) {
      if (col != '0') {
        continue;
      }
      const auto temp = getSummits(puzzle, Posn(rowIndex, colIndex));
      std::cout << "Done with at (" << rowIndex << ',' << colIndex
                << ") result=" << temp << std::endl;
      answer += temp;
    }
  }
  std::cout << "Answer: " << answer << std::endl;
}