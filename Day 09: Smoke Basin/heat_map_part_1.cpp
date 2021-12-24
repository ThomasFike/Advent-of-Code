/**
 * @file heat_map_part_1.cpp
 * @author Thomas Fike
 */
#include "../reuse.hpp"

// #include <string_view>

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

static constexpr INPUT_FILE_TYPE input_file = INPUT_FILE_TYPE::LARGE;
static constexpr FILE_INFO file_info = get_file_info(input_file);

void print_heatmap(const std::array<std::array<int, file_info.H_SIZE>,
                                    file_info.V_SIZE>& heat_map) {
  for (const auto& row : heat_map) {
    for (const auto& entry : row) {
      std::cout << entry;
    }
    std::cout << std::endl;
  }
}

int find_risk_score(const std::array<std::array<int, file_info.H_SIZE>,
                                     file_info.V_SIZE>& heat_map);

int main() {
  std::array<std::array<int, file_info.H_SIZE>, file_info.V_SIZE> heat_map;
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
  const auto risk_score = find_risk_score(heat_map);
  std::cout << "Risk_score: " << risk_score << std::endl;
}

/**
 * @brief Find the risk_score for a given heat_map
 *
 * @param heat_map
 * @return int
 */
int find_risk_score(const std::array<std::array<int, file_info.H_SIZE>,
                                     file_info.V_SIZE>& heat_map) {
  std::array<std::array<int, file_info.H_SIZE>, file_info.V_SIZE> depth_map;
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
  return total;
}