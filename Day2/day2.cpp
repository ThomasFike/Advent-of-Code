/**
 * @file day2.cpp
 */
#include <map>

#include "common.hpp"

enum class RPS { ROCK = 1, PAPER, SCISSORS };
enum class DISPOSITION { WON, LOST, DRAW };

const std::map<char, RPS> char_to_rps = {
    {'A', RPS::ROCK}, {'B', RPS::PAPER}, {'C', RPS::SCISSORS},
    {'X', RPS::ROCK}, {'Y', RPS::PAPER}, {'Z', RPS::SCISSORS}};
const std::map<DISPOSITION, int> score_from_result = {
    {DISPOSITION::WON, 6}, {DISPOSITION::LOST, 0}, {DISPOSITION::DRAW, 3}};

static DISPOSITION result_of_match(const std::pair<RPS, RPS>& match);

std::ostream& operator<<(std::ostream& stream, const RPS& rps) {
  switch (rps) {
    case RPS::ROCK:
      stream << "Rock";
      break;
    case RPS::PAPER:
      stream << "Paper";
      break;
    case RPS::SCISSORS:
      stream << "Scissors";
      break;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const DISPOSITION& disp) {
  switch (disp) {
    case DISPOSITION::WON:
      stream << "Won";
      break;
    case DISPOSITION::DRAW:
      stream << "Draw";
      break;
    case DISPOSITION::LOST:
      stream << "Lost";
      break;
  }
  return stream;
}

int main() {
  std::ifstream in_file("part1.txt");
  int total_score = 0;
  while (in_file.good()) {
    std::string line;
    std::getline(in_file, line);
    std::pair<RPS, RPS> match(char_to_rps.at(line[2]), char_to_rps.at(line[0]));
    auto result = result_of_match(match);
    std::cout << match.first << " vs " << match.second << " resulted in "
              << result << std::endl;

    total_score += score_from_result.at(result);
    total_score += static_cast<int>(match.first);
  }
  std::cout << "Total Score: " << total_score << std::endl;
}

static DISPOSITION result_of_match(const std::pair<RPS, RPS>& match) {
  switch (match.first) {
    case RPS::ROCK:
      switch (match.second) {
        case RPS::ROCK:
          return DISPOSITION::DRAW;
        case RPS::PAPER:
          return DISPOSITION::LOST;
        case RPS::SCISSORS:
          return DISPOSITION::WON;
      }
      break;
    case RPS::PAPER:
      switch (match.second) {
        case RPS::ROCK:
          return DISPOSITION::WON;
        case RPS::PAPER:
          return DISPOSITION::DRAW;
        case RPS::SCISSORS:
          return DISPOSITION::LOST;
      }
      break;
    case RPS::SCISSORS:
      switch (match.second) {
        case RPS::ROCK:
          return DISPOSITION::LOST;
        case RPS::PAPER:
          return DISPOSITION::WON;
        case RPS::SCISSORS:
          return DISPOSITION::DRAW;
      }
      break;
  }
  return DISPOSITION::LOST;
}