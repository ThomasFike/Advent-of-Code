/**
 * @file heat_map_part_1.cpp
 * @author Thomas Fike
 */
#include "../reuse.hpp"

#include <bitset>

enum class INPUT_FILE_TYPE { SMALL, LARGE };

struct FILE_INFO {
  std::string_view FILE_NAME = "";
  int H_SIZE = 0;
  int V_SIZE = 0;
};

constexpr FILE_INFO get_file_info(INPUT_FILE_TYPE file) {
  FILE_INFO info;
  switch (file) {
    case INPUT_FILE_TYPE::SMALL: {
      info.FILE_NAME = "small.txt";
      info.H_SIZE = 10;
      info.V_SIZE = 5;
      break;
    }
    case INPUT_FILE_TYPE::LARGE: {
      info.FILE_NAME = "input.txt";
      info.H_SIZE = 100;
      info.V_SIZE = 100;
      break;
    }
    default: {
      break;
    }
  }
  return info;
}

static constexpr INPUT_FILE_TYPE input_file = INPUT_FILE_TYPE::SMALL;
static constexpr FILE_INFO file_info = get_file_info(input_file);

using GRID = std::array<std::array<int, file_info.H_SIZE>, file_info.V_SIZE>;

void print_heatmap(const GRID& heat_map) {
  for (const auto& row : heat_map) {
    for (const auto& entry : row) {
      std::cout << entry;
    }
    std::cout << std::endl;
  }
}

int find_mult_of_3_l_basin(const GRID& heat_map);
std::vector<int> get_basins(const GRID& heat_map, const GRID& depth_map);

int main() {
  GRID heat_map;
  for (auto& row : heat_map) {
    row.fill(0);
  }
  {
    std::ifstream input_fs(file_info.FILE_NAME.data());
    for (auto& row : heat_map) {
      for (auto& entry : row) {
        char temp;
        input_fs >> temp;
        entry = int(temp - '0');
      }
    }
  }
  const auto risk_score = find_mult_of_3_l_basin(heat_map);
  std::cout << "Risk_score: " << risk_score << std::endl;
}

/**
 * @brief Find the risk_score for a given heat_map
 *
 * @param heat_map
 * @return int
 */
int find_mult_of_3_l_basin(const GRID& heat_map) {
  GRID depth_map;
  for (auto& row : depth_map) {
    row.fill(0);
  }
  // Check middle
  for (int row = 1; row < file_info.V_SIZE - 1; row++) {
    for (int col = 1; col < file_info.H_SIZE - 1; col++) {
      // Check all 4 directions
      if ((heat_map[row][col] < heat_map[row][col - 1]     // Left
           && heat_map[row][col] < heat_map[row][col + 1]  // Right
           && heat_map[row][col] < heat_map[row - 1][col]  // Up
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    }
  }
  // Check Top
  for (int col = 0; col < file_info.H_SIZE; col++) {
    const int row = 0;
    if (col == 0) {
      if ((heat_map[row][col] < heat_map[row][col + 1]     // Right
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    } else if (col == file_info.H_SIZE - 1) {
      if ((heat_map[row][col] < heat_map[row][col - 1]     // Left
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    } else {
      if ((heat_map[row][col] < heat_map[row][col - 1]     // Left
           && heat_map[row][col] < heat_map[row][col + 1]  // Right
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    }
  }
  // Check Bottom
  for (int col = 0; col < file_info.H_SIZE; col++) {
    const int row = file_info.V_SIZE - 1;
    if (col == 0) {
      if ((heat_map[row][col] < heat_map[row][col + 1]     // Right
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    } else if (col == file_info.H_SIZE - 1) {
      if ((heat_map[row][col] < heat_map[row][col - 1]     // Left
           && heat_map[row][col] < heat_map[row + 1][col]  // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    } else {
      if ((heat_map[row][col] < heat_map[row][col - 1]     // Left
           && heat_map[row][col] < heat_map[row][col + 1]  // Right
           && heat_map[row][col] < heat_map[row - 1][col]  // Up
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    }
  }
  // Check Left
  // Check Right
  for (int row = 1; row < file_info.V_SIZE - 1; row++) {
    for (int col = 0; col <= file_info.H_SIZE - 1;
         col += file_info.H_SIZE - 1) {
      int side_offset = 0;
      if (col == 0) {
        side_offset = 1;
      } else {
        side_offset = -1;
      }
      if ((heat_map[row][col] < heat_map[row][col + side_offset]  // Side
           && heat_map[row][col] < heat_map[row - 1][col]         // Up
           && heat_map[row][col] < heat_map[row + 1][col]         // down
           )) {
        depth_map[row][col] = heat_map[row][col] + 1;
      }
    }
  }
  int total = 0;
  for (const auto& row : depth_map) {
    total += std::accumulate(row.begin(), row.end(), 0);
  }
  get_basins(heat_map, depth_map);
  return total;
}

enum DIRECTIONS { UP, DOWN, LEFT, RIGHT, DIRECTIONS_COUNT };

std::bitset<DIRECTIONS_COUNT> get_lower_directions(std::pair<int, int> location,
                                                   const GRID& heat_map);

/**
 * @brief Get the basins in a heat_map
 *
 * @param heat_map
 * @param depth_map
 * @return std::vector<int>
 */
std::vector<int> get_basins(const GRID& heat_map, const GRID& depth_map) {
  std::vector<int> basins;
  for (int row = 0; row < file_info.V_SIZE; row++) {
    for (int col = 0; col < file_info.H_SIZE; col++) {
      if (depth_map[row][col] != 0) {
      } else {
      }
    }
  }
  std::bitset<DIRECTIONS_COUNT> dir = get_lower_directions({0, 0}, heat_map);
  return basins;
}

std::bitset<DIRECTIONS_COUNT> get_lower_directions(std::pair<int, int> location,
                                                   const GRID& heat_map) {
  std::bitset<DIRECTIONS_COUNT> directions;
  std::bitset<DIRECTIONS_COUNT> directions_to_check;
  const int row = location.first;
  const int col = location.second;
  if (row > 0) {
    directions_to_check.set(UP);
  }
  if (row < file_info.V_SIZE - 1) {
    directions_to_check.set(DOWN);
  }
  if (col > 0) {
    directions_to_check.set(LEFT);
  }
  if (col < file_info.H_SIZE - 1) {
    directions_to_check.set(RIGHT);
  }

  const int depth = heat_map[row][col];

  if (directions_to_check.test(UP)) {
    if (depth < heat_map[row - 1][col] && heat_map[row - 1][col] != 9) {
      directions.set(UP);
    }
  }
  if (directions_to_check.test(DOWN)) {
    if (depth < heat_map[row + 1][col] && heat_map[row + 1][col] != 9) {
      directions.set(DOWN);
    }
  }
  if (directions_to_check.test(LEFT)) {
    if (depth < heat_map[row][col - 1] && heat_map[row][col - 1] != 9) {
      directions.set(LEFT);
    }
  }
  if (directions_to_check.test(RIGHT)) {
    if (depth < heat_map[row][col + 1] && heat_map[row][col + 1] != 9) {
      directions.set(RIGHT);
    }
  }

  return directions;
}