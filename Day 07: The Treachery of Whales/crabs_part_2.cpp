/**
 * @file crabs_part_2.cpp
 * @author Thomas Fike
 */

#include "../reuse.hpp"
#include <limits>

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.good()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  std::vector<int> positions = read_comma_seperated_file<int>(input_file);
  std::sort(positions.begin(), positions.end());
  int best_position = 0;
  int best_fuel_required = std::numeric_limits<int>::max();
  for (int curent_position = 0;
       curent_position <= *max_element(positions.begin(), positions.end());
       curent_position++) {
    const auto distance = [curent_position](int previous, int check_pos) {
      int total = 0;
      for (int i = 1; i <= abs(curent_position - check_pos); i++) {
        total += i;
      }
      return (previous + total);
    };
    const auto fuel_requiered =
        std::accumulate(positions.begin(), positions.end(), 0, distance);
    if (fuel_requiered < best_fuel_required) {
      best_position = curent_position;
      best_fuel_required = fuel_requiered;
    }
  }

  std::cout << "Position: " << best_position << std::endl;
  std::cout << "Fuel Needed: " << best_fuel_required << std::endl;
}