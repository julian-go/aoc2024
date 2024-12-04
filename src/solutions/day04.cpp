#include <array>
#include <iostream>
#include <sstream>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

aoc::Matrix2D<char> GetWordSearch(std::ifstream& in) {
  std::string line{};

  std::getline(in, line);
  int size = std::ssize(line);
  aoc::Matrix2D<char> word_search(size, size);

  int y{0};
  do {
    int x{0};
    for (auto const& c : line) {
      word_search.at(x, y) = c;
      ++x;
    }
    ++y;
  } while (std::getline(in, line));

  return word_search;
}

}  // namespace

std::string Day04_1(std::ifstream& in) {
  auto word_search = GetWordSearch(in);
  auto Xs = std::vector<aoc::Vector2D<int>>{};

  // Find all Xs in the word search
  for (int y = 0; y < word_search.sizeY(); ++y) {
    for (int x = 0; x < word_search.sizeX(); ++x) {
      if (word_search.at(x, y) == 'X') {
        Xs.push_back({x, y});
      }
    }
  }

  constexpr std::string_view kMas = "MAS";
  constexpr std::array<aoc::Vector2D<int>, 8> kDirections = {
      aoc::Vector2D<int>{0, 1},   aoc::Vector2D<int>{-1, 1}, aoc::Vector2D<int>{-1, 0},
      aoc::Vector2D<int>{-1, -1}, aoc::Vector2D<int>{0, -1}, aoc::Vector2D<int>{1, -1},
      aoc::Vector2D<int>{1, 0},   aoc::Vector2D<int>{1, 1}};
  int xmas_found{0};

  // Check all Xs in all directions (cardinal and ordinal) to see if they spell XMAS
  for (auto const& X : Xs) {
    for (auto const& dir : kDirections) {
      int i = 1;
      bool found_xmas{true};
      for (auto const& next_letter : kMas) {
        auto next_letter_xy = X + dir * i;
        if (!(word_search.contains(next_letter_xy) &&
              word_search.at(next_letter_xy) == next_letter)) {
          found_xmas = false;
          break;
        }
        ++i;
      }
      if (found_xmas) {
        ++xmas_found;
      }
    }
  }
  return std::to_string(xmas_found);
};

std::string Day04_2(std::ifstream& in) {
  auto word_search = GetWordSearch(in);
  auto As = std::vector<aoc::Vector2D<int>>{};

  // Find all Xs in the word search
  for (int y = 0; y < word_search.sizeY(); ++y) {
    for (int x = 0; x < word_search.sizeX(); ++x) {
      if (word_search.at(x, y) == 'A') {
        As.push_back({x, y});
      }
    }
  }

  int matches{0};
  // Check all Xs
  for (auto const& A : As) {
    if (word_search.contains(A.x - 1, A.y - 1) && word_search.contains(A.x - 1, A.y + 1) &&
        word_search.contains(A.x + 1, A.y - 1) && word_search.contains(A.x + 1, A.y + 1)) {
      if (word_search.at(A.North().West()) == 'M' && word_search.at(A.North().East()) == 'M' &&
          word_search.at(A.South().West()) == 'S' && word_search.at(A.South().East()) == 'S') {
        ++matches;
      }
      if (word_search.at(A.North().West()) == 'M' && word_search.at(A.North().East()) == 'S' &&
          word_search.at(A.South().West()) == 'M' && word_search.at(A.South().East()) == 'S') {
        ++matches;
      }
      if (word_search.at(A.North().West()) == 'S' && word_search.at(A.North().East()) == 'S' &&
          word_search.at(A.South().West()) == 'M' && word_search.at(A.South().East()) == 'M') {
        ++matches;
      }
      if (word_search.at(A.North().West()) == 'S' && word_search.at(A.North().East()) == 'M' &&
          word_search.at(A.South().West()) == 'S' && word_search.at(A.South().East()) == 'M') {
        ++matches;
      }
    }
  }
  return std::to_string(matches);
};