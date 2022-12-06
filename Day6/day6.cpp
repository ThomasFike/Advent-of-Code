/**
 * @file day6.cpp
 */

#include "common.hpp"

template <size_t SIZE>
class Viewer {
 public:
  Viewer(void) { data.fill('\0'); }
  void addItem(const char item) {
    const auto findIter = std::find(data.begin(), data.end(), '\0');
    if (findIter != data.end()) {
      *findIter = item;
    } else {
      std::rotate(data.begin(), data.begin() + 1, data.end());
      data[data.size() - 1] = item;
    }
  }

  [[nodiscard]] bool unique(void) const {
    auto copy = data;
    std::sort(copy.begin(), copy.end());
    return std::unique(copy.begin(), copy.end()) == copy.end() && isFilled();
  }

  [[nodiscard]] const std::array<char, SIZE>& getData(void) const {
    return data;
  }

 private:
  std::array<char, SIZE> data;
  bool isFilled(void) const {
    const auto findIter = std::find(data.begin(), data.end(), '\0');
    return findIter == data.end();
  }
};

int main() {
  std::ifstream inFile("part1.txt");
  Viewer<14> viewer;
  int counter = 0;
  while (inFile.good()) {
    char temp;
    inFile >> temp;
    viewer.addItem(temp);
    counter++;
    if (viewer.unique()) {
      break;
    }
  }
  fmt::print("Done {}\n", counter);
}
