/**
 * @file day7.cpp
 */

#include <list>
#include <regex>

#include "common.hpp"

struct File {
  std::string name;
  size_t size = 0;
};

size_t addFiles(size_t current, const File& file) {
  return current + file.size;
}

struct Directory {
  Directory* parent;
  std::string name;
  std::list<File> files;
  std::list<Directory> dirs;
  size_t size = 0;

  bool isBottom(void) const { return dirs.empty(); }
  void getSizeOfFiles(void) {
    size = static_cast<size_t>(
        std::accumulate(files.cbegin(), files.cend(), 0, addFiles));
  }
  std::string getPath(void) {
    auto ptr = this;
    std::string path = name;
    while (ptr->parent != nullptr) {
      path = ptr->parent->name + "/" + path;
      ptr = ptr->parent;
    }
    return path;
  }
  size_t getLevel(void) {
    size_t count = 0;
    auto ptr = this;
    while (ptr->parent != nullptr) {
      count++;
      ptr = ptr->parent;
    }
    return count + 1;
  }
};

enum CMD { CD, LS };

std::optional<std::pair<CMD, std::string>> getCMD(const std::string& line) {
  std::regex CdRegex("^\\$ cd ([\\w/.]*)");
  std::regex LsRegex("^\\$ ls");
  if (std::smatch match; std::regex_match(line, match, CdRegex)) {
    return {{CMD::CD, match.str(1)}};
  } else if (std::regex_search(line, LsRegex)) {
    return {{CMD::LS, ""}};
  } else {
    return {};
  }
}

int main() {
  std::ifstream inFile("part1.txt");
  Directory topDir;
  topDir.name = "/";
  std::vector<Directory*> dirs;
  Directory* currentDir = &topDir;
  while (inFile.good()) {
    const std::string line = get_line(inFile);
    const auto cmdRet = getCMD(line);
    if (cmdRet) {
      auto [cmd, dir] = cmdRet.value();
      switch (cmd) {
        case CMD::CD:
          if (dir == "..") {
            currentDir = (*currentDir).parent;
          } else {
            for (auto iter = currentDir->dirs.begin();
                 iter != currentDir->dirs.end(); iter++) {
              if (iter->name == dir) {
                currentDir = &*iter;
                break;
              }
            }
          }
          // fmt::print("CMD CD {}\n", currentDir->name);
          break;
        case CMD::LS:
          // fmt::print("CMD LS\n");
          break;
      }
    } else {
      if (line.substr(0, 3) == "dir") {
        Directory newDir;
        newDir.name = line.substr(4, line.length() - 4);
        newDir.parent = currentDir;
        // fmt::print("New Dir {}\n", newDir.name);
        currentDir->dirs.emplace_back(std::move(newDir));
        dirs.emplace_back(&(currentDir->dirs.back()));
      } else {
        const std::regex reg(R"~((\d+) ([\w.]+))~");
        std::smatch match;
        std::regex_match(line, match, reg);
        File file;
        file.name = match[2];
        file.size = std::stoul(match[1]);
        // fmt::print("New File {} of size {}\n", file.name, file.size);
        currentDir->files.emplace_back(std::move(file));
      }
    }
  }
  std::vector<std::vector<Directory*>> organized(20);
  for (auto* dir : dirs) {
    const auto depth = dir->getLevel();
    organized[depth].emplace_back(dir);
    dir->getSizeOfFiles();
  }
  for (auto iter = organized.rbegin(); iter != organized.rend(); iter++) {
    for (auto* dir : *iter) {
      dir->parent->size += dir->size;
    }
  }
  unsigned long long total = 0;
  for (auto* dir : dirs) {
    if (dir->size <= 100000) {
      total += dir->size;
    }
    fmt::print("Dir {} of size {}\n", dir->getPath(), dir->size);
  }
  fmt::print("Total {}\n", total);
}
