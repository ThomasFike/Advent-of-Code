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

struct File {
  File(const int aId, const int aSize) : mId(aId), mSize(aSize) {}
  File(const int aSize) : mId(EmptySlot), mSize(aSize) {}
  int mId;
  int mSize;
  bool IsFreeSpace() const { return mId == EmptySlot; }
};

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

[[maybe_unused]] static void printDisk(const std::vector<File>& disk) {
  for (const auto& item : disk) {
    if (item.IsFreeSpace()) {
      for (int i = 0; i < item.mSize; i++) {
        std::cout << '.';
      }
    } else {
      for (int i = 0; i < item.mSize; i++) {
        std::cout << item.mId;
      }
    }
  }
  std::cout << std::endl;
}

static uint64_t calcChecksum(const std::vector<File>& disk) {
  uint64_t position = 0;
  uint64_t checksum = 0;
  for (const auto& item : disk) {
    const auto positionAfter = position + item.mSize;
    if (item.IsFreeSpace()) {
      position = positionAfter;
      continue;
    }
    for (; position < positionAfter; position++) {
      checksum += (position * item.mId);
    }
  }
  return checksum;
}

int main() {
  std::ifstream inputFile(FileName);
  int fileId = 0;
  std::vector<File> disk;

  while (inputFile.good()) {
    char temp;
    inputFile >> temp;
    const auto fileSize = convertCharToInt(temp);
    disk.emplace_back(fileId, fileSize);

    fileId++;
    inputFile >> temp;
    const auto emptySize = convertCharToInt(temp);
    if (emptySize > 0) {
      disk.emplace_back(emptySize);
    }
  }

  if (disk.back().IsFreeSpace()) {
    disk.pop_back();
  }

  printDisk(disk);

  for (size_t backPosn = disk.size() - 1; backPosn > 0; backPosn--) {
    if (disk[backPosn].IsFreeSpace()) {
      continue;
    }

    const auto searchEnd = disk.begin() + backPosn;
    const auto insertLoc =
        std::find_if(disk.begin(), disk.begin() + backPosn,
                     [neededSize = disk[backPosn].mSize](const File& aFile) {
                       return aFile.IsFreeSpace() && aFile.mSize >= neededSize;
                     });
    if (insertLoc != searchEnd) {
      const auto fId = disk[backPosn].mId;
      const auto extraSize = insertLoc->mSize - disk[backPosn].mSize;
      disk[backPosn].mId = EmptySlot;
      insertLoc->mSize -= extraSize;
      insertLoc->mId = fId;
      if ((insertLoc + 1)->IsFreeSpace()) {
        (insertLoc + 1)->mSize += extraSize;
      } else {
        disk.insert(insertLoc + 1, File(extraSize));
        backPosn++;
      }
    }
  }
  printDisk(disk);
  const auto answer = calcChecksum(disk);
  std::cout << "Answer: " << answer << std::endl;
}