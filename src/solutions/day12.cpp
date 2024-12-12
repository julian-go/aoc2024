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

int Area(Cache& c, const Map& map, Vector position) {
  const auto id = map.at(position);
  std::queue<Vector> to_check;
  to_check.push(position);
  c.insert(position);
  int area = 1;
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
  }
  std::cout << area << std::endl;

  return area;
}

int Perimeter(const Map& map, Vector position) {
  auto start = position;
  const auto id = map.at(position);
  int perimeter = 0;
  Vector previous_direction = Vector(0, 1);
  auto initial_direction = previous_direction;
  do {
    Vector direction;
    for (auto n : position.Neighbors()) {
      if (map.contains(n) && map.at(n) == id) {
        direction = n - position;
      }
    }
    perimeter++;
    if (previous_direction.x != direction.x) {
      perimeter++;
    }
    if (previous_direction.y != direction.y) {
      perimeter++;
    }
    direction = direction;
  } while (position != start);
  if (previous_direction.y != initial_direction.y) {
    perimeter++;
  }
  return perimeter;
}

int Visit(Cache& c, const Map& map, Vector position) {
  if (c.contains(position)) {
    return 0;
  } else {
    return Area(c, map, position) * Perimeter(map, position);
  }
}
}  // namespace

std::string Day12_1(std::ifstream& in) {
  auto map = ParseInput(in);
  int value = 0;
  Cache c;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeX(); ++x) {
      value += Visit(c, map, {x, y});
    }
  }
  return "";
};

std::string Day12_2(std::ifstream& in) { return ""; };