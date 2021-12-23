/**
 * @file crabs_part_1.cpp
 * @author Thomas Fike
 */

#include "../reuse.hpp"

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.good()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  std::vector<int> positions = read_comma_seperated_file<int>(input_file);
  std::sort(positions.begin(), positions.end());
  const auto best_location = positions[int(positions.size() / 2)];
  const auto distance = [best_location](int previous, int check_pos) {
    return (previous + abs(best_location - check_pos));
  };
  const auto fuel_requiered =
      std::accumulate(positions.begin(), positions.end(), 0, distance);
  std::cout << "Position: " << best_location << std::endl;
  std::cout << "Fuel Needed: " << fuel_requiered << std::endl;
}