#include <iostream>
#include <set>
#include <sstream>
#include <tuple>
#include <utility>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

using OccupationMap = aoc::Matrix2D<bool>;

namespace {
auto GetMap(std::ifstream& in) {
  std::string line{};
  in >> line;
  auto map = OccupationMap(std::ssize(line), std::ssize(line), false);
  auto start_position = aoc::Vector2D<int>();
  auto start_orientation = aoc::Vector2D<int>();
  int y{0};
  do {
    int x{0};
    for (const auto& c : line) {
      map.set(x, y, c == '#');
      if (c == '^') {
        start_position = {x, y};
        start_orientation = {0, -1};
      }
      ++x;
    }
    ++y;
  } while (in >> line);
  return std::tuple{map, start_position, start_orientation};
}
}  // namespace

std::string Day06_1(std::ifstream& in) {
  auto [map, position, orientation] = GetMap(in);

  bool done = false;
  std::set<aoc::Vector2D<int>> visited;
  while (!done) {
    visited.insert(position);
    // Check facing
    if (!map.contains(position + orientation)) {
      done = true;
    } else {
      if (map.at(position + orientation)) {
        orientation.RotateRight();
      } else {
        position += orientation;
      }
    }
  }
  return std::to_string(std::ssize(visited));
};

std::string Day06_2(std::ifstream& in) {
  // go go brute force :)
  auto [map, start_position, start_orientation] = GetMap(in);
  int loop_positions = 0;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeX(); ++x) {
      auto obstacled_map = map;
      if (obstacled_map.at(x, y)) {
        continue;
      }
      obstacled_map.set(x, y, true);

      auto position = start_position;
      auto orientation = start_orientation;

      // try with new map
      bool done = false;
      std::set<std::pair<aoc::Vector2D<int>, aoc::Vector2D<int>>> visited;
      visited.insert({position, orientation});
      while (!done) {
        // Check facing
        if (!obstacled_map.contains(position + orientation)) {
          done = true;
        } else {
          if (obstacled_map.at(position + orientation)) {
            orientation.RotateRight();
          } else {
            position += orientation;

            // if we have been here before, loop!
            if (visited.contains({position, orientation})) {
              done = true;
              loop_positions++;
            }
            visited.insert({position, orientation});
          }
        }
      }
    }
  }

  return std::to_string(loop_positions);
};