#include <deque>
#include <iostream>
#include <numeric>
#include <unordered_set>

#include "solutions.hpp"

namespace {

struct Block {
  Block(int id, int size) : id{id}, size{size} {};
  bool IsFree() const { return id == -1 && size > 0; }
  bool IsData() const { return id != -1 && size > 0; }
  int id;
  int size;
};

template <class T>
auto ParseInput(std::ifstream& in) {
  std::string line{};
  std::getline(in, line);
  T layout{};
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
  return layout;
}

}  // namespace

std::string Day09_1(std::ifstream& in) {
  std::vector<Block> layout = ParseInput<std::vector<Block>>(in);

  std::int64_t checksum = 0;
  std::int64_t current_memory_loc = 0;

  for (auto block = layout.begin(), to_move = layout.end() - 1; block != layout.end(); ++block) {
    if (!block->IsFree()) {
      for (int i = 0; i < block->size; ++i, ++current_memory_loc) {
        checksum += current_memory_loc * block->id;
      }
    } else {
      for (int i = 0; i < block->size; ++i, ++current_memory_loc) {
        // Find the first available data block from the back
        while (to_move > block && !to_move->IsData()) {
          to_move--;
        }
        if (to_move > block) {
          // Move it to the front
          to_move->size--;
          checksum += current_memory_loc * to_move->id;
        }
      }
    }
  }

  return std::to_string(checksum);
}

std::string Day09_2(std::ifstream& in) {
  // It just works (Tm)
  // Needs some cleaning up, but it does the job
  auto layout = ParseInput<std::deque<Block>>(in);

  int j = std::ssize(layout) - 1;
  int moved = 1e10;
  while (j >= 0) {
    if (layout[j].id != -1 && layout[j].size > 0 && layout[j].id < moved) {
      moved = layout[j].id;
      for (int i = 0; i <= j; ++i) {
        // search for a space [j] that can fit the element [j]
        if (layout[i].id == -1 && layout[i].size >= layout[j].size) {
          // it fits
          layout[i].size -= layout[j].size;
          auto tmp = layout[j];

          // turn allocated space intro free space
          layout[j].id = -1;
          if (j > 0 && layout[j - 1].id == -1) {
            // merge with space to the left
            layout[j - 1].size += layout[j].size;
            layout[j].size = 0;
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
    while (layout[i].id != -1 && layout[i].size > 0) {
      checksum += current_memory_loc * layout[i].id;
      layout[i].size--;
      current_memory_loc++;
    }
    if (layout[i].id == -1) {
      current_memory_loc += layout[i].size;
    }
  }
  return std::to_string(checksum);
}