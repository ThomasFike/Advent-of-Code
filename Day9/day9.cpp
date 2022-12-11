/**
 * @file day9.cpp
 */

#include <fmt/ostream.h>

#include <forward_list>

#include "common.hpp"

template <typename T>
class Highest {
 public:
  Highest(void) : max({}) {}
  void operator=(const T& val) {
    if (max.has_value()) {
      if (val > max.value()) {
        max = val;
      }
    } else {
      max = val;
    }
  }
  T operator()(void) { return max.value(); }

 private:
  std::optional<T> max;
};

enum Direction { Up, Down, Left, Right };

struct Position {
  int x;
  int y;
  bool operator==(const Position& second) const {
    return ((x == second.x) && (y == second.y));
  }
  bool operator<(const Position& second) const {
    return (x < second.x || y < second.y);
  }
  friend std::ostream& operator<<(std::ostream& out, const Position& pos);
};
template <>
struct fmt::formatter<Position> : ostream_formatter {};

class Rope {
 public:
  Rope(void) : head({0, 0}), pastHead({0, 0}), tail({0, 0}) {}
  void doMove(Direction dir);
  size_t getTailCount(void) const;

 private:
  class TailCounter {
   public:
    void addPos(Position aPos) {
      if (std::none_of(tailPos.cbegin(), tailPos.cend(),
                       [&](const auto& testPos) { return testPos == aPos; })) {
        tailPos.emplace_back(aPos);
      }
    }

    size_t size(void) const {
      auto temp = tailPos;
      // std::sort(temp.begin(), temp.end());
      fmt::print("Sorted: \n{}\n", temp);
      return tailPos.size();
    }

   private:
    std::vector<Position> tailPos;
  };

  Position head;
  Position pastHead;
  Position tail;
  TailCounter tailCounter;

  void moveHead(Position aPos);
  void moveTail(void);
  bool isDiagonal(void) const;
  bool isNextTo(void) const;
};

Direction DirectionFromChar(const char c);

int main() {
  std::ifstream inFile("part1.txt");
  Rope rope;
  Highest<int> max;
  int total = 0;
  while (inFile.good()) {
    const auto line = get_line(inFile);
    const auto dir = DirectionFromChar(line[0]);
    const auto count = std::stoi(line.substr(2, line.size()));
    max = count;
    for (auto i = 0; i < count; i++) {
      rope.doMove(dir);
      total++;
    }
  }
  const auto count = rope.getTailCount();
  fmt::print("Count: {}\n", count);
  fmt::print("Max: {}\n", max());
  fmt::print("Total: {}\n", total);
}

Direction DirectionFromChar(const char c) {
  switch (c) {
    case 'U':
      return Direction::Up;
    case 'D':
      return Direction::Down;
    case 'L':
      return Direction::Left;
    case 'R':
      return Direction::Right;
    default:
      throw std::logic_error("Could not convert char");
      return Direction::Up;
  }
}

std::ostream& operator<<(std::ostream& out, const Position& pos) {
  fmt::print(out, "({},{})", pos.x, pos.y);
  return out;
}

void Rope::doMove(Direction dir) {
  pastHead = head;
  switch (dir) {
    case Direction::Up:
      moveHead({head.x, head.y + 1});
      break;
    case Direction::Down:
      moveHead({head.x, head.y - 1});
      break;
    case Direction::Left:
      moveHead({head.x - 1, head.y});
      break;
    case Direction::Right:
      moveHead({head.x + 1, head.y});
  }
  try {
    moveTail();
  } catch (const std::exception& e) {
    fmt::print("Error: {}\n", e.what());
    fmt::print("Head: {}, Tail: {}\n", head, tail);
    exit(-1);
  }
  // fmt::print("Head: {}, Tail: {}\n", head, tail);
}

size_t Rope::getTailCount(void) const { return tailCounter.size(); }

void Rope::moveHead(Position aPos) { head = aPos; }

void Rope::moveTail(void) {
  tailCounter.addPos(tail);
  if (isDiagonal() || isNextTo()) {
    if (abs(head.x - tail.x) + abs(tail.y - head.y) > 2) {
      throw std::logic_error("Not Diagonal");
    }
    // Position is good so return
    return;
  }
  tail = pastHead;
  if (!(isNextTo())) {
    throw std::logic_error("Fail");
  }
}

bool Rope::isDiagonal(void) const {
  auto isXpm1 = [&]() {
    return ((head.x == tail.x + 1) || (head.x == tail.x - 1));
  };
  // If one row above Above
  if (tail.y == head.y + 1) {
    return isXpm1();
  }
  // If one row Below
  else if (tail.y == head.y - 1) {
    return isXpm1();
  } else {
    return false;
  }
}

bool Rope::isNextTo(void) const {
  return (abs(head.x - tail.x) + abs(tail.y - head.y) <= 1);
}