/**
 * @file lines_part_1.cpp
 * @author Thomas Fike
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <sstream>
#include <algorithm>
#include <numeric>

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
};

std::ostream& operator<<(std::ostream& out, const Point& point) {
  out << '(' << point.x << ',' << point.y << ')';
  return out;
}

bool operator==(const Point& first, const Point& second) {
  if (first.x != second.x) return false;
  if (first.y != second.y) return false;
  return true;
}

bool operator!=(const Point& first, const Point& second) {
  return !(first == second);
}

struct Line {
  Point start;
  Point end;
  std::vector<Point> line_points;
  bool is_straight_line = true;
  Line(Point start, Point end);

 private:
  std::vector<Point> generate_diagonal_points(Point start, Point end);
};

Line::Line(Point start, Point end) : start(start), end(end) {
  if (start.x == end.x) {
    line_points.reserve(abs(start.y - end.y) + 2);
    if (start.y < end.y) {
      for (int current_y = start.y; current_y <= end.y; current_y++) {
        line_points.emplace_back(start.x, current_y);
      }
    } else {
      for (int current_y = start.y; current_y >= end.y; current_y--) {
        line_points.emplace_back(start.x, current_y);
      }
    }
  } else if (start.y == end.y) {
    line_points.reserve(abs(start.x - end.x) + 2);
    if (start.x < end.x) {
      for (int current_x = start.x; current_x <= end.x; current_x++) {
        line_points.emplace_back(current_x, start.y);
      }
    } else {
      for (int current_x = start.x; current_x >= end.x; current_x--) {
        line_points.emplace_back(current_x, start.y);
      }
    }
  } else {
    line_points = generate_diagonal_points(start, end);
    is_straight_line = false;
  }
}

std::vector<Point> Line::generate_diagonal_points(Point start, Point end) {
  std::vector<Point> points;
  points.reserve(abs(start.y - end.y) + 2);

  Point adjusted_start;
  Point adjusted_end;
  adjusted_start.x = std::min(start.x, end.x);
  if (adjusted_start.x == start.x) {
    adjusted_start.y = start.y;
    adjusted_end = end;
  } else {
    adjusted_start.y = end.y;
    adjusted_end = start;
  }

  if (adjusted_start.y < adjusted_end.y) {
    for (int x = adjusted_start.x, y = adjusted_start.y;
         (x <= adjusted_end.x) && (y <= adjusted_end.y); x++, y++) {
      points.emplace_back(x, y);
    }
  } else {
    for (int x = adjusted_start.x, y = adjusted_start.y;
         (x <= adjusted_end.x) && (y >= adjusted_end.y); x++, y--) {
      points.emplace_back(x, y);
    }
  }
  return points;
}

template <typename T>
void print_vector(std::vector<T> vec) {
  for (const auto& i : vec) {
    std::cout << i;
    if (i != vec.back()) {
      std::cout << ',';
    }
  }
  std::cout << std::endl;
}

[[nodiscard]] std::pair<Point, Point> get_start_end(std::istream& input);

static const int GRID_SIZE = 1000;

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.good()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }
  std::vector<Line> lines;
  while (input_file.good()) {
    const auto [start, end] = get_start_end(input_file);
    if (start.x > GRID_SIZE || start.y > GRID_SIZE || end.x > GRID_SIZE ||
        end.y > GRID_SIZE) {
      std::cout << "!!!!!!POINT LARGER THAN GRID SIZE!!!!!!" << std::endl;
      return 1;
    }
    const Line line(start, end);
    lines.push_back(line);
    // print_vector(lines.back().line_points);
  }

  std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid_of_lines;
  for (auto& row : grid_of_lines) {
    for (auto& item : row) {
      item = 0;
    }
  }

  for (const auto& line : lines) {
    for (const auto& point : line.line_points) {
      grid_of_lines[point.y][point.x]++;
    }
  }

  auto count_in_row = [](int previous, std::array<int, GRID_SIZE> row) {
    return previous +
           std::count_if(row.begin(), row.end(), [](int x) { return x >= 2; });
  };
  const auto amount_over_2 = std::accumulate(
      grid_of_lines.begin(), grid_of_lines.end(), 0, count_in_row);
  std::cout << "Over 2: " << amount_over_2 << std::endl;
}

[[nodiscard]] std::pair<Point, Point> get_start_end(std::istream& input) {
  std::string line;
  getline(input, line);
  std::stringstream line_stream(line);
  Point start;
  Point end;
  char temp;
  line_stream >> start.x >> temp >> start.y;
  line_stream >> temp >> temp;
  line_stream >> end.x >> temp >> end.y;
  return {start, end};
}