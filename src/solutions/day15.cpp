#include <iostream>
#include <numeric>
#include <sstream>
#include <tuple>
#include <unordered_set>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {
using Vector = aoc::Vector2D<int>;

struct Map {
  Vector size{};
  Vector robot_position{};
  std::unordered_set<Vector, Vector::Hash> boxes;
  std::unordered_set<Vector, Vector::Hash> walls;
};

auto ParseInput(std::ifstream& in) {
  Map map{};
  std::vector<Vector> moves{};

  std::string line{};
  std::getline(in, line);
  map.size = Vector(std::ssize(line), std::ssize(line));

  int y = 0;
  do {
    int x = 0;
    for (const auto& c : line) {
      if (c == '#') {
        map.walls.insert({x, y});
      } else if (c == 'O') {
        map.boxes.insert({x, y});
      } else if (c == '@') {
        map.robot_position = {x, y};
      }
      ++x;
    }
    ++y;
    std::getline(in, line);
  } while (!line.empty());

  while (std::getline(in, line)) {
    for (const auto& c : line) {
      if (c == '^') {
        moves.push_back({0, -1});
      } else if (c == 'v') {
        moves.push_back({0, 1});
      } else if (c == '<') {
        moves.push_back({-1, 0});
      } else if (c == '>') {
        moves.push_back({1, 0});
      }
    }
  }

  return std::tuple{map, moves};
}

void Draw(const Map& map) {
  for (int y = 0; y < map.size.y; ++y) {
    for (int x = 0; x < map.size.x; ++x) {
      if (map.walls.contains({x, y})) {
        std::cout << '#';
      } else if (map.boxes.contains({x, y})) {
        std::cout << 'O';
      } else if (map.robot_position.x == x && map.robot_position.y == y) {
        std::cout << '@';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Move(Map& map, Vector move) {
  auto move_to = map.robot_position + move;
  const auto is_box = [&map](Vector v) { return map.boxes.contains(v); };
  const auto is_wall = [&map](Vector v) { return map.walls.contains(v); };
  if (is_wall(move_to)) {
    return;
  } else if (is_box(move_to)) {
    // Need to check if the box can be moved here
    auto next_position = move_to;
    do {
      next_position += move;
    } while (is_box(next_position));

    if (is_wall(next_position)) {
      // cannot move the boxes
      return;
    }

    map.boxes.insert(next_position);
    map.boxes.erase(move_to);
    map.robot_position = move_to;

  } else {
    map.robot_position = move_to;
  }
}

}  // namespace

std::string Day15_1(std::ifstream& in) {
  auto [map, moves] = ParseInput(in);
  for (const auto& move : moves) {
    Move(map, move);
  }
  auto score = std::accumulate(map.boxes.begin(), map.boxes.end(), 0,
                               [](const auto& a, const auto& b) { return a + b.x + 100 * b.y; });
  return std::to_string(score);
};

std::string Day15_2(std::ifstream& in) { return ""; };