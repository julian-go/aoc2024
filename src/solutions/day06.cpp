#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include <utility>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

using ObstacleMap = aoc::Matrix2D<bool>;
using Vector = aoc::Vector2D<int>;

struct Hash {
  std::size_t operator()(const std::pair<Vector, Vector>& v) const {
    return (static_cast<std::uint64_t>(v.first.x) << 32 | static_cast<std::uint64_t>(v.first.y)) ^
           (static_cast<std::uint64_t>(v.second.x) << 32 | static_cast<std::uint64_t>(v.second.y));
  }
};

using PositionCache = std::unordered_set<Vector, Vector::Hash>;
using OrientationCache = std::unordered_set<std::pair<Vector, Vector>, Hash>;

auto GetMap(std::ifstream& in) {
  std::string line{};
  in >> line;
  auto map = ObstacleMap(std::ssize(line), std::ssize(line), false);
  auto start_position = Vector();
  auto start_orientation = Vector();
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

auto Part1(ObstacleMap obstacles, Vector position, Vector orientation) {
  PositionCache visited;
  visited.insert(position);
  while (obstacles.contains(position + orientation)) {
    if (obstacles.at(position + orientation)) {
      orientation.RotateRight();
    } else {
      position += orientation;
      visited.insert(position);
    }
  }
  return visited;
}

bool Check(const ObstacleMap& obstacles, Vector position, Vector orientation,
           const OrientationCache& initial_cache) {
  OrientationCache cache;
  while (obstacles.contains(position + orientation)) {
    if (obstacles.at(position + orientation)) {
      orientation.RotateRight();
    } else {
      position += orientation;
      if (cache.contains({position, orientation}) ||
          initial_cache.contains({position, orientation})) {
        // this is a loop
        return true;
      }
      cache.insert({position, orientation});
    }
  }
  return false;
}

auto Part2(ObstacleMap obstacles, Vector position, Vector orientation) {
  OrientationCache cache;
  PositionCache obstacle_locations_checked;
  int loop_locations{0};
  while (obstacles.contains(position + orientation)) {
    const auto next_position = position + orientation;
    if (obstacles.at(next_position)) {
      orientation.RotateRight();
    } else {
      if (!obstacle_locations_checked.contains(next_position)) {
        obstacle_locations_checked.insert(next_position);
        obstacles.set(next_position, true);  // set a temporary obstacle
        if (Check(obstacles, position, orientation, cache)) {
          loop_locations++;
        }
        obstacles.set(next_position, false);  // remove the temporary obstacle
      }
      position += orientation;
      cache.insert({position, orientation});
    }
  }
  return loop_locations;
}

}  // namespace

std::string Day06_1(std::ifstream& in) {
  auto [map, position, orientation] = GetMap(in);
  auto visited = Part1(map, position, orientation);
  return std::to_string(std::ssize(visited));
};

std::string Day06_2(std::ifstream& in) {
  auto [map, position, orientation] = GetMap(in);
  auto loop_locations = Part2(map, position, orientation);
  return std::to_string(loop_locations);
};