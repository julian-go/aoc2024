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

  int matches{0};
  // Check all Xs
  for (auto const& X : Xs) {
    if (word_search.contains(X.x, X.y - 3)) {
      if (word_search.at(X.North()) == 'M' && word_search.at(X.North().North()) == 'A' &&
          word_search.at(X.North().North().North()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x, X.y + 3)) {
      if (word_search.at(X.South()) == 'M' && word_search.at(X.South().South()) == 'A' &&
          word_search.at(X.South().South().South()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x - 3, X.y)) {
      if (word_search.at(X.West()) == 'M' && word_search.at(X.West().West()) == 'A' &&
          word_search.at(X.West().West().West()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x + 3, X.y)) {
      if (word_search.at(X.East()) == 'M' && word_search.at(X.East().East()) == 'A' &&
          word_search.at(X.East().East().East()) == 'S') {
        ++matches;
      }
    }

    // diagonal
    if (word_search.contains(X.x - 3, X.y - 3)) {
      if (word_search.at(X.North().West()) == 'M' &&
          word_search.at(X.North().West().North().West()) == 'A' &&
          word_search.at(X.North().West().North().West().North().West()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x + 3, X.y - 3)) {
      if (word_search.at(X.North().East()) == 'M' &&
          word_search.at(X.North().East().North().East()) == 'A' &&
          word_search.at(X.North().East().North().East().North().East()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x - 3, X.y + 3)) {
      if (word_search.at(X.South().West()) == 'M' &&
          word_search.at(X.South().West().South().West()) == 'A' &&
          word_search.at(X.South().West().South().West().South().West()) == 'S') {
        ++matches;
      }
    }
    if (word_search.contains(X.x + 3, X.y + 3)) {
      if (word_search.at(X.South().East()) == 'M' &&
          word_search.at(X.South().East().South().East()) == 'A' &&
          word_search.at(X.South().East().South().East().South().East()) == 'S') {
        ++matches;
      }
    }
  }
  return std::to_string(matches);
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