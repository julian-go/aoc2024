#include <deque>
#include <iostream>
#include <unordered_set>

#include "solutions.hpp"

namespace {

struct Block {
  Block(int id, int unallocated_space) : id{id}, unallocated_space{unallocated_space} {};
  int id;
  int unallocated_space;
};

}  // namespace

std::string Day09_1(std::ifstream& in) {
  std::string line{};
  std::getline(in, line);
  std::vector<Block> layout{};
  bool is_block{true};
  int id = 0;
  for (const auto& c : line) {
    if (is_block) {
      layout.emplace_back(id, c - '0');
      ++id;
    } else {
      layout.emplace_back(-1, c - '0');
    }
    is_block = !is_block;
  }

  std::int64_t checksum = 0;
  std::int64_t current_memory_loc = 0;
  for (int i = 0; i < layout.size(); ++i) {
    if (layout[i].id != -1) {
      for (int m = 0; m < layout[i].unallocated_space; ++m, ++current_memory_loc) {
        checksum += current_memory_loc * layout[i].id;
        // std::cout << layout[i].first;
      }
    } else {
      for (int m = 0; m < layout[i].unallocated_space; ++m, ++current_memory_loc) {
        for (int j = std::ssize(layout) - 1; j >= 0 && j > i; --j) {
          if (layout[j].id != -1) {
            // pull to front
            if (layout[j].unallocated_space > 0) {
              layout[j].unallocated_space--;
              checksum += current_memory_loc * layout[j].id;
              // std::cout << layout[j].first;
              break;
            }
          }
        }
      }
    }
  }
  return std::to_string(checksum);
}

std::string Day09_2(std::ifstream& in) {
  // It just works (Tm)
  // Needs some cleaning up, but it does the job
  std::string line{};
  std::getline(in, line);
  std::deque<Block> layout{};
  bool is_block{true};
  int id = 0;
  for (const auto& c : line) {
    if (is_block) {
      layout.emplace_back(id, c - '0');
      ++id;
    } else {
      layout.emplace_back(-1, c - '0');
    }
    is_block = !is_block;
  }

  int j = std::ssize(layout) - 1;
  int moved = 1e10;
  while (j >= 0) {
    if (layout[j].id != -1 && layout[j].unallocated_space > 0 && layout[j].id < moved) {
      moved = layout[j].id;
      for (int i = 0; i <= j; ++i) {
        // search for a space [j] that can fit the element [j]
        if (layout[i].id == -1 && layout[i].unallocated_space >= layout[j].unallocated_space) {
          // it fits
          layout[i].unallocated_space -= layout[j].unallocated_space;
          auto tmp = layout[j];

          // turn allocated space intro free space
          layout[j].id = -1;
          if (j > 0 && layout[j - 1].id == -1) {
            // merge with space to the left
            layout[j - 1].unallocated_space += layout[j].unallocated_space;
            layout[j].unallocated_space = 0;
          }
          layout.insert(layout.begin() + i, tmp);
          break;
        }
      }
      --j;
    } else {
      --j;
    }
  }

  std::int64_t checksum = 0;
  std::int64_t current_memory_loc = 0;
  for (int i = 0; i < std::ssize(layout); ++i) {
    while (layout[i].id != -1 && layout[i].unallocated_space > 0) {
      checksum += current_memory_loc * layout[i].id;
      layout[i].unallocated_space--;
      current_memory_loc++;
    }
    if (layout[i].id == -1) {
      current_memory_loc += layout[i].unallocated_space;
    }
  }
  return std::to_string(checksum);
}