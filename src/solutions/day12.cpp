#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>;

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

using Vector = aoc::Vector2D<int>;
using Cache = std::unordered_set<Vector, Vector::Hash>;
using Map = aoc::Matrix2D<char>;

auto ParseInput(std::ifstream& in) {
  std::string line{};
  std::getline(in, line);
  auto map = Map(std::ssize(line), std::ssize(line));
  int y = 0;
  do {
    int x = 0;
    for (auto c : line) {
      map.at(x, y) = c;
      ++x;
    }
    ++y;
  } while (std::getline(in, line));
  return map;
}

int Part1(Cache& c, const Map& map, Vector position) {
  if (c.contains(position)) {
    return 0;
  }

  int area = 1;  // start at one to include initial element
  int perimeter = 0;
  const auto id = map.at(position);
  std::queue<Vector> to_check;
  to_check.push(position);
  c.insert(position);

  while (!to_check.empty()) {
    auto current = to_check.front();
    to_check.pop();

    for (auto n : current.Neighbors()) {
      if (!c.contains(n) && map.contains(n) && map.at(n) == id) {
        to_check.push(n);
        c.insert(n);
        area++;
      } else if (!map.contains(n) || map.at(n) != id) {
        perimeter++;
      }
    }
  }
  return area * perimeter;
}

int Part2(Cache& c, const Map& map, Vector position) {
  if (c.contains(position)) {
    return 0;
  }

  int area = 1;  // start at one to include initial element
  int corners = 0;
  const auto id = map.at(position);
  const auto can_walk = [&map, id](Vector v) { return map.contains(v) && map.at(v) == id; };

  std::queue<Vector> to_check;
  to_check.push(position);
  c.insert(position);

  while (!to_check.empty()) {
    auto current = to_check.front();
    to_check.pop();

    for (auto n : current.Neighbors()) {
      if (!c.contains(n) && map.contains(n) && map.at(n) == id) {
        to_check.push(n);
        c.insert(n);
        area++;
      }
    }

    // In part 2 we use the flood fill to identify all corner blocks, since the number of vertices
    // equals the number of sides
    {
      auto wall_1 = Vector(-1, 0);
      auto wall_2 = Vector(0, -1);
      for (int i = 0; i < 4; ++i) {
        if (!can_walk(current + wall_1) && !can_walk(current + wall_2)) {
          corners++;
        }
        wall_1.RotateRight();
        wall_2.RotateRight();
      }
    }

    {
      auto free_1 = Vector(-1, 0);
      auto free_2 = Vector(0, -1);
      auto wall_1 = Vector(-1, -1);
      for (int i = 0; i < 4; ++i) {
        if (can_walk(current + free_1) && can_walk(current + free_2) &&
            !can_walk(current + wall_1)) {
          corners++;
        }
        free_1.RotateRight();
        free_2.RotateRight();
        wall_1.RotateRight();
      }
    }
  }
  int sides = corners;
  return area * sides;
}

}  // namespace

std::string Day12_1(std::ifstream& in) {
  auto map = ParseInput(in);
  int value = 0;
  Cache c;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeX(); ++x) {
      value += Part1(c, map, {x, y});
    }
  }
  return std::to_string(value);
};

std::string Day12_2(std::ifstream& in) {
  auto map = ParseInput(in);
  int value = 0;
  Cache c;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeX(); ++x) {
      if (!c.contains({x, y})) {
        value += Part2(c, map, {x, y});
      }
    }
  }
  return std::to_string(value);
};