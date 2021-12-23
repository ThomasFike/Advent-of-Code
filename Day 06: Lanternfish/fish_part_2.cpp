/**
 * @file fish_part_2.cpp
 * @author Thomas Fike
 * Idea taken from:
 * https://www.reddit.com/r/adventofcode/comments/ra70c2/comment/hngfu8q/?utm_source=share&utm_medium=web2x&context=3
 */

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <iomanip>
#include <numeric>

using fish_count_type = unsigned long long;

static fish_count_type sum_of_fish(const std::array<fish_count_type, 9> fish);

int main() {
  std::array<fish_count_type, 9> fish_in_each_state;
  fish_in_each_state.fill(0);
  {
    std::vector<int> fish;
    fish.reserve(500);
    std::ifstream input_file("input.txt");
    if (!input_file.good()) {
      std::cout << "Failed to open file" << std::endl;
      return 1;
    }
    while (input_file.good()) {
      char throw_away_char;
      int temp;
      input_file >> temp >> throw_away_char;
      fish.emplace_back(temp);
    }

    for (const auto& i : fish) {
      if (i < 0 || i > 8) {
        std::cout << "!!! Invalid Entry !!!";
      } else {
        fish_in_each_state[i]++;
      }
    }
  }

  const int NUMBER_OF_DAYS = 256;

  for (int day = 1; day <= NUMBER_OF_DAYS; day++) {
    const fish_count_type fish_at_zero = fish_in_each_state[0];
    for (int i = 0; i <= 7; i++) {
      fish_in_each_state[i] = fish_in_each_state[i + 1];
    }
    fish_in_each_state[6] += fish_at_zero;
    fish_in_each_state[8] = fish_at_zero;
  }
  const fish_count_type number_of_fish = sum_of_fish(fish_in_each_state);
  std::cout << "Number of Fish at the end of " << NUMBER_OF_DAYS
            << " days: " << number_of_fish << std::endl;
}

static fish_count_type sum_of_fish(const std::array<fish_count_type, 9> fish) {
  fish_count_type sum = 0;
  for (const auto& i : fish) {
    sum += i;
  }
  return sum;
}