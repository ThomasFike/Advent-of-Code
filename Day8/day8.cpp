/**
 * @file day8.cpp
 */

#include "common.hpp"

using Row = std::vector<int>;
using Grid = std::vector<Row>;

class Viewer {
 public:
  enum Direction { Up, Down, Left, Right };
  explicit Viewer(std::reference_wrapper<Grid> aGrid) : grid(aGrid) {}
  int countVisible(size_t row, size_t col) {
    const std::array<Direction, 4> Directions = {
        Direction::Up, Direction::Down, Direction::Left, Direction::Right};
    return static_cast<int>(std::count_if(
        Directions.begin(), Directions.end(), [&](const auto dir) {
          return isVisible(static_cast<long>(row), static_cast<long>(col), dir);
        }));
  }

 private:
  Viewer() = delete;
  bool isVisible(const long row, const long col, Direction dir);
  int getTree(long row, long col) const {
    return grid[static_cast<size_t>(row)][static_cast<size_t>(col)];
  }
  Grid& grid;
};

bool Viewer::isVisible(const long row, const long col, Direction dir) {
  const long LeftIdx = 0;
  const long TopIdx = 0;
  const long RightIdx = static_cast<long>(grid[0].size());
  const long BottomIdx = static_cast<long>(grid.size());

  const int tree = getTree(row, col);

  switch (dir) {
    case Direction::Up:
      for (long i = row - 1; i >= TopIdx; i--) {
        // fmt::print("Up ({}, {}) vs ({}, {})\n", row, col, i, col);
        if (getTree(i, col) >= tree) {
          return false;
        }
      }
      break;

    case Direction::Down:
      for (long i = row + 1; i < BottomIdx; i++) {
        // fmt::print("Down ({}, {}) vs ({}, {})\n", row, col, i, col);
        if (getTree(i, col) >= tree) {
          return false;
        }
      }
      break;

    case Direction::Left:
      for (long i = col - 1; i >= LeftIdx; i--) {
        // fmt::print("Left ({}, {}) vs ({}, {})\n", row, col, row, i);
        if (getTree(row, i) >= tree) {
          return false;
        }
      }
      break;
    case Direction::Right:
      for (long i = col + 1; i < RightIdx; i++) {
        // fmt::print("Right ({}, {}) vs ({}, {})\n", row, col, row, i);
        if (getTree(row, i) >= tree) {
          return false;
        }
      }
      break;
  }
  return true;
}

Grid getInput(std::ifstream& in) {
  Grid grid;
  while (in.good()) {
    const std::string line = get_line(in);
    Row row;
    std::transform(line.cbegin(), line.cend(), std::back_inserter(row),
                   convertCharToInt);
    grid.emplace_back(std::move(row));
  }
  return grid;
}

int main() {
  std::ifstream inFile("part1.txt");
  Grid grid = getInput(inFile);
  Viewer viewer(std::ref(grid));
  int count = 0;
  for (size_t row = 1; row < grid.size() - 1; row++) {
    for (size_t col = 1; col < grid[0].size() - 1; col++) {
      if (viewer.countVisible(row, col)) {
        fmt::print("Found at {},{}\n", row, col);
        count++;
      }
    }
  }

  count += static_cast<int>(2 * grid.size());
  count += static_cast<int>(2 * (grid[0].size() - 2));

  fmt::print("Count: {}\n", count);
}
