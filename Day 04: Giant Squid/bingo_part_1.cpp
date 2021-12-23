/**
 * @file bingo_part_1.cpp
 * @author Thomas Fike
 */

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>

static const int GRID_SIZE = 5;

using Board = std::array<std::array<int, GRID_SIZE>, GRID_SIZE>;

class Bingo {
 public:
  Bingo(std::istream& input);
  void mark(int marker);
  bool check_for_winner() const;
  int get_sum_of_winner() const;
  void print_board() const;

 private:
  Board full_board;
  Board in_progress_board;
};

/**
 * @brief Construct a new Bingo object
 *
 * @param input
 */
Bingo::Bingo(std::istream& input) {
  for (auto& row : full_board) {
    for (auto& item : row) {
      input >> item;
    }
  }
  std::array<int, GRID_SIZE> empty_row;
  empty_row.fill(-1);
  in_progress_board.fill(empty_row);
}

/**
 * @brief Mark a new spot
 * @details Determines if the spot exists and if so mark it.
 *
 * @param marker numerical value for the spot being marked
 */
void Bingo::mark(int marker) {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      if (full_board[row][col] == marker) {
        in_progress_board[row][col] = full_board[row][col];
      }
    }
  }
}

/**
 * @brief Determine if the board has won
 *
 * @return true This card has won
 * @return false This card has not won
 */
bool Bingo::check_for_winner() const {
  const auto value_present = [](int item) { return (item != -1); };
  const auto is_complete = [value_present](std::array<int, GRID_SIZE> line) {
    return (std::all_of(line.begin(), line.end(), value_present));
  };
  // Check Rows
  for (int row = 0; row < GRID_SIZE; row++) {
    if (is_complete(in_progress_board[row])) {
      return true;
    }
  }
  // Check Columns
  for (int col = 0; col < GRID_SIZE; col++) {
    std::array<int, GRID_SIZE> column;
    for (int i = 0; i < GRID_SIZE; i++) {
      column[i] = in_progress_board[i][col];
    }
    if (is_complete(column)) {
      return true;
    }
  }
  return false;
}

int Bingo::get_sum_of_winner() const {
  int sum = 0;
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      if (in_progress_board[row][col] == -1) {
        sum += full_board[row][col];
      }
    }
  }
  return sum;
}

/**
 * @brief print out a board to the standard output
 *
 */
void Bingo::print_board() const {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      if (full_board[row][col] == in_progress_board[row][col]) {
        std::cout << std::setw(3);
        std::cout << 'X';
      } else {
        std::cout << std::setw(3);
        std::cout << full_board[row][col];
      }
    }
    std::cout << std::endl;
  }
}

static std::vector<int> get_numbers(std::istream& input_file);

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.good()) {
    std::cout << "File did not exist" << std::endl;
    return 2;
  }
  const auto numbers = get_numbers(input_file);

  std::vector<Bingo> boards;
  boards.reserve(10);
  while (input_file.good()) {
    boards.emplace_back(input_file);
  }
  boards.shrink_to_fit();

  for (const auto number : numbers) {
    for (auto& board : boards) {
      board.mark(number);
      if (board.check_for_winner()) {
        std::cout << "Winner:" << std::endl;
        board.print_board();
        const int score = number * board.get_sum_of_winner();
        std::cout << "Winning Score: " << score << std::endl;
        return 0;
      }
    }
    std::cout << "No one won from " << number << std::endl;
  }
}

/**
 * @brief Get the numbers from a single line of the input file
 * @note Values should be comma seperated without spaces
 * @pre input_file should be at the first elelment of the list
 *
 * @param input_file
 * @return std::vector<int>
 */
static std::vector<int> get_numbers(std::istream& input_file) {
  std::string temp;
  getline(input_file, temp);
  std::stringstream number_list(temp);

  std::vector<int> numbers;
  numbers.reserve(100);
  while (number_list.good()) {
    int number = 0;
    number_list >> number;
    char throw_away;
    number_list >> throw_away;
    numbers.push_back(number);
  }
  numbers.shrink_to_fit();
  return numbers;
}