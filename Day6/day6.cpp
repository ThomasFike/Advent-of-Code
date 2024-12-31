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

enum class Direction { Up, Right, Down, Left };

using Posn = std::pair<int, int>;
struct Guard {
  Posn mPosn;
  Direction mDirection;
  void TurnRight() {
    switch (mDirection) {
      case Direction::Up:
        mDirection = Direction::Right;
        break;
      case Direction::Right:
        mDirection = Direction::Down;
        break;
      case Direction::Down:
        mDirection = Direction::Left;
        break;
      case Direction::Left:
        mDirection = Direction::Up;
        break;
    }
  }
  Posn CalcNextPosn() const {
    Posn posn = mPosn;
    switch (mDirection) {
      case Direction::Up:
        posn.first--;
        break;
      case Direction::Down:
        posn.first++;
        break;
      case Direction::Right:
        posn.second++;
        break;
      case Direction::Left:
        posn.second--;
        break;
    }
    return posn;
  }
};

int main() {
  std::ifstream inputFile(FileName);

  std::set<Posn> barriers;
  int rowCount = 0;
  int colCount = 0;
  Guard guard{{0, 0}, Direction::Up};

  while (inputFile.good()) {
    std::string line;
    getline(inputFile, line);
    if (colCount == 0) {
      colCount = line.size();
    }
    for (const auto [col, item] : std::ranges::enumerate_view(line)) {
      switch (item) {
        case '^': {
          guard.mPosn = Posn{rowCount, col};
        } break;

        case '#': {
          barriers.emplace(rowCount, col);
        }
        default:
          break;
      }
    }
    rowCount++;
  }
  // for (const auto& b : barriers) {
  //   std::cout << "Barrier: (" << b.first << ',' << b.second << ')' <<
  //   std::endl;
  // }
  // std::cout << "Guard: (" << guard.mPosn.first << ',' << guard.mPosn.second
  //           << ')' << std::endl;

  const auto isGuardOutsideBoard = [&]() {
    return (guard.mPosn.first < 0 || guard.mPosn.first >= rowCount ||
            guard.mPosn.second < 0 || guard.mPosn.second >= colCount);
  };

  // int moveCount;
  std::set<Posn> visited;

  while (!isGuardOutsideBoard()) {
    visited.insert(guard.mPosn);
    auto nextPosn = guard.CalcNextPosn();
    while (barriers.contains(nextPosn)) {
      guard.TurnRight();
      nextPosn = guard.CalcNextPosn();
      // std::cout << "Turn right" << std::endl;
    }
    // std::cout << "Moving" << std::endl;
    guard.mPosn = nextPosn;
  }

  std::cout << "Answer: " << visited.size() << std::endl;
}