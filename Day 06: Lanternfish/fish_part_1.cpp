/**
 * @file fish_part_1.cpp
 * @author Thomas Fike
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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

int main() {
  std::vector<int> fish;
  fish.reserve(10000);
  {
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
  }

  const int NUMBER_OF_DAYS = 80;
  bool do_prints = (fish.size() < 10);
  if (do_prints) {
    std::cout << "Inital State: ";
    print_vector(fish);
  }

  for (int i = 1; i <= NUMBER_OF_DAYS; i++) {
    int number_of_fish_to_add = 0;
    for (auto& fish_i : fish) {
      if (fish_i == 0) {
        fish_i = 6;
        number_of_fish_to_add++;
      } else {
        fish_i--;
      }
    }
    for (int i = 0; i < number_of_fish_to_add; i++) {
      fish.emplace_back(8);
    }
    if (do_prints && (i <= 0)) {
      std::cout << "After " << std::setw(2) << i << " days: ";
      print_vector(fish);
    } else {
      std::cout << "Number of Fish at the end of " << i
                << " days: " << fish.size() << std::endl;
    }
  }
  std::cout << "Number of Fish at the end of " << NUMBER_OF_DAYS
            << " days: " << fish.size() << std::endl;
}
