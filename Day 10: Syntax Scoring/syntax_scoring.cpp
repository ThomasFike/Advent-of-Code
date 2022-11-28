/**
 * @file syntax_scoring.cpp
 * @author Thomas Fike
 */
#include "../reuse.hpp"

#include <map>
#include <stack>
#include <ctype.h>

static constexpr std::array<std::pair<char, char>, 4> pairs = {
    {{'(', ')'}, {'{', '}'}, {'[', ']'}, {'<', '>'}}};

static const std::map<char, int> corrupt_point_values = {
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

static const std::map<char, int> complete_point_values = {
    {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

static std::map<char, int> occurrences = {
    {')', 0}, {']', 0}, {'}', 0}, {'>', 0}};

static std::vector<uint64_t> complete_points;

bool is_complete(const std::string& line);
bool is_corrupt(const std::string& line);
char get_opposite(const char& symbol);
bool is_open(const char& symbol);
void get_complete_store(std::stack<char> remaining);

int main() {
  std::ifstream file("input.txt");
  std::vector<std::string> lines;
  std::string str;
  while (getline(file, str)) {
    lines.emplace_back(str);
  }
  for (const auto& line : lines) {
    if (!is_complete(line)) {
      is_corrupt(line);
    }
  }
  // Compute the number of points
  int points = 0;
  for (const auto& [item, count] : occurrences) {
    points += corrupt_point_values.at(item) * count;
  }
  std::cout << "Total points: " << points << std::endl;
  std::sort(complete_points.begin(), complete_points.end());
  std::cout << "Complete points: "
            << complete_points[complete_points.size() / 2] << std::endl;
}

bool is_complete(const std::string& line) {
  std::map<char, int> counter = {{'(', 0}, {'[', 0}, {'{', 0}, {'<', 0},
                                 {')', 0}, {']', 0}, {'}', 0}, {'>', 0}};
  for (const auto& symbol : line) {
    counter.at(symbol)++;
  }
  // for (const auto& [key, value] : counter) {
  //   std::cout << key << ": " << value << std::endl;
  // }
  for (const auto& pair : pairs) {
    if (counter.at(pair.first) != counter.at(pair.second)) {
      // std::cout << "Bad Pair" << pair.first << pair.second << std::endl;
      return false;
    }
  }
  return true;
}

bool is_corrupt(const std::string& line) {
  std::stack<char> openings;
  for (const char& symbol : line) {
    if (is_open(symbol)) {
      openings.push(symbol);
    } else {
      const auto expected_closing = get_opposite(openings.top());
      if (expected_closing != symbol) {
        std::cout << "Expected " << expected_closing << " got " << symbol
                  << std::endl;
        occurrences.at(symbol)++;
        return true;
      } else {
        openings.pop();
      }
    }
  }
  get_complete_store(openings);
  return false;
}

char get_opposite(const char& symbol) {
  for (const auto& pair : pairs) {
    if (symbol == pair.first) {
      return pair.second;
    } else if (symbol == pair.second) {
      return pair.first;
    }
  }
  return '\0';
}

bool is_open(const char& symbol) {
  for (const auto& pair : pairs) {
    if (symbol == pair.first) {
      return true;
    } else if (symbol == pair.second) {
      return false;
    }
  }
  return false;
}

void get_complete_store(std::stack<char> remaining) {
  uint64_t points = 0;
  while (remaining.size()) {
    const auto item = remaining.top();
    remaining.pop();

    points *= 5;
    points += complete_point_values.at(get_opposite(item));
  }
  complete_points.emplace_back(points);
}