#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include <utility>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

using Map = aoc::Matrix2D<int>;
using Coordinate = aoc::Vector2D<int>;

auto ParseInput(std::ifstream& in) {
  std::string line{};
  in >> line;
  auto map = Map(std::ssize(line), std::ssize(line), -1);
  auto start_positions = std::vector<Coordinate>{};
  int y{0};
  do {
    int x{0};
    for (const auto& c : line) {
      map.at(x, y) = static_cast<int>(c - '0');
      if (map.at(x, y) == 0) {
        start_positions.emplace_back(x, y);
      }
      ++x;
    }
    ++y;
  } while (in >> line);
  return std::tuple{map, start_positions};
}

}  // namespace

std::string Day10_1(std::ifstream& in) {
  auto [map, start_positions] = ParseInput(in);

  std::vector<std::pair<Coordinate, Coordinate>> last_positions;
  for (const auto& p : start_positions) {
    last_positions.emplace_back(p, p);
  }

  for (int i = 1; i <= 9; ++i) {
    std::vector<std::pair<Coordinate, Coordinate>> positions{};
    for (auto& p : last_positions) {
      for (auto& n : p.first.Neighbors()) {
        if (map.contains(n) && map.at(n) == i) {
          positions.emplace_back(n, p.second);
        }
      }
    }
    last_positions = positions;
  }

  std::sort(last_positions.begin(), last_positions.end());
  auto last = std::unique(last_positions.begin(), last_positions.end());
  last_positions.erase(last, last_positions.end());
  return std::to_string(std::ssize(last_positions));
};

std::string Day10_2(std::ifstream& in) {
  auto [map, start_positions] = ParseInput(in);

  std::vector<std::pair<Coordinate, Coordinate>> last_positions;
  for (const auto& p : start_positions) {
    last_positions.emplace_back(p, p);
  }

  for (int i = 1; i <= 9; ++i) {
    std::vector<std::pair<Coordinate, Coordinate>> positions{};
    for (auto& p : last_positions) {
      for (auto& n : p.first.Neighbors()) {
        if (map.contains(n) && map.at(n) == i) {
          positions.emplace_back(n, p.second);
        }
      }
    }
    last_positions = positions;
  }

  return std::to_string(std::ssize(last_positions));
};