/**
 * @file day9.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>
#include <set>
#include <utility>
#include <vector>

static const auto FileName = "part1.txt";

static constexpr int EmptySlot = -1;

int convertCharToInt(const char letter) {
  switch (letter) {
    case '9':
      return 9;
      break;
    case '8':
      return 8;
      break;
    case '7':
      return 7;
      break;
    case '6':
      return 6;
      break;
    case '5':
      return 5;
      break;
    case '4':
      return 4;
      break;
    case '3':
      return 3;
      break;
    case '2':
      return 2;
      break;
    case '1':
      return 1;
      break;
    default:
    case '0':
      return 0;
      break;
  }
}

[[maybe_unused]] static void printDisk(const std::vector<int>& disk) {
  for (const auto item : disk) {
    if (item == EmptySlot) {
      std::cout << '.';
    } else {
      std::cout << item;
    }
  }
  std::cout << std::endl;
}

static uint64_t calcChecksum(const std::vector<int>& disk) {
  uint64_t checksum = 0;
  for (size_t i = 0; i < disk.size(); i++) {
    const auto fileId = disk[i];
    if (fileId != EmptySlot) {
      checksum += (fileId * i);
    }
  }
  return checksum;
}

int main() {
  std::ifstream inputFile(FileName);
  int fileId = 0;
  std::vector<int> disk;
  const auto addFile = [&](const int aFileId, const int fileSize) {
    for (int i = 0; i < fileSize; i++) {
      disk.emplace_back(aFileId);
    }
  };

  while (inputFile.good()) {
    char temp;
    inputFile >> temp;
    const auto fileSize = convertCharToInt(temp);
    addFile(fileId, fileSize);

    fileId++;
    inputFile >> temp;
    const auto emptySize = convertCharToInt(temp);
    addFile(EmptySlot, emptySize);
  }

  auto endIter = disk.end();
  for (endIter--; *endIter == EmptySlot && endIter != disk.begin(); endIter--) {
  }
  disk.erase(endIter + 1, disk.end());

  // printDisk(disk);

  const auto isDiskCompact = [&]() {
    const auto firstEmpty = std::find(disk.begin(), disk.end(), EmptySlot);
    return std::none_of(firstEmpty, disk.end(),
                        [](const auto item) { return item != EmptySlot; });
  };

  for (size_t backPosn = disk.size() - 1; backPosn > 0 && !isDiskCompact();
       backPosn--) {
    const auto moveFileId = disk[backPosn];
    if (moveFileId == EmptySlot) {
      continue;
    }
    const auto nextPosn = std::find(disk.begin(), disk.end(), EmptySlot);
    if (nextPosn == disk.end()) {
      throw std::logic_error("Somehow didn't find empty");
    }
    *nextPosn = moveFileId;
    disk[backPosn] = EmptySlot;
  }

  // printDisk(disk);

  const auto answer = calcChecksum(disk);
  std::cout << "Answer: " << answer << std::endl;
}