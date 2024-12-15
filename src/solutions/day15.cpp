#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
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

struct WideMap {
  Vector size{};
  Vector robot_position{};
  std::unordered_map<Vector, int, Vector::Hash> box_id;
  std::unordered_map<int, std::array<Vector, 2>> id_box;
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

auto ParseInputPart2(std::ifstream& in) {
  WideMap map{};
  std::vector<Vector> moves{};

  std::string line{};
  std::getline(in, line);
  map.size = Vector(std::ssize(line) * 2, std::ssize(line));

  int y = 0;
  int id = 0;
  do {
    int x = 0;
    for (const auto& c : line) {
      if (c == '#') {
        map.walls.insert({x, y});
        map.walls.insert({x + 1, y});
      } else if (c == 'O') {
        map.box_id[{x, y}] = id;
        map.box_id[{x + 1, y}] = id;
        map.id_box[id] = {Vector{x, y}, Vector{x + 1, y}};
        id++;
      } else if (c == '@') {
        map.robot_position = {x, y};
      }
      x += 2;
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

void DrawPart2(const WideMap& map) {
  for (int y = 0; y < map.size.y; ++y) {
    for (int x = 0; x < map.size.x; ++x) {
      if (map.walls.contains({x, y})) {
        std::cout << '#';
      } else if (map.box_id.contains({x, y})) {
        if (map.box_id.contains({x + 1, y})) {
          if (map.box_id.at({x, y}) == map.box_id.at({x + 1, y})) {
            std::cout << "[]";
          }
        }
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

void MovePart2(WideMap& map, Vector move) {
  auto move_to = map.robot_position + move;
  const auto is_box = [&map](Vector v) { return map.box_id.contains(v); };
  const auto is_wall = [&map](Vector v) { return map.walls.contains(v); };
  if (is_wall(move_to)) {
    return;
  } else if (move.y == 0 && is_box(move_to)) {
    // horizontal move treat same as part 1
    // Need to check if the box can be moved here
    auto free_position = move_to;
    do {
      free_position += move;
    } while (is_box(free_position));

    if (is_wall(free_position)) {
      // cannot move the boxes
      return;
    }

    free_position -= move;
    while (free_position != map.robot_position) {
      auto id = map.box_id[free_position];
      auto pos = map.id_box[id];
      map.box_id.erase(pos[0]);
      map.box_id.erase(pos[1]);
      pos[0] += move;
      pos[1] += move;
      map.box_id[pos[0]] = id;
      map.box_id[pos[1]] = id;
      map.id_box[id] = pos;
      free_position -= move * 2;
    }

    map.robot_position = move_to;
  } else if (move.y != 0 && is_box(move_to)) {
    // First build a list of movable and affected boxes
    bool done = false;
    std::stack<Vector> spaces_to_check;
    spaces_to_check.push(move_to);
    std::unordered_set<int> boxes_to_move;
    while (!spaces_to_check.empty()) {
      auto space = spaces_to_check.top();
      spaces_to_check.pop();

      if (is_box(space)) {
        // If we find a box in a sapce we need to get all spaces occupied by that box and add all
        // spaces in move direction of the box for checking
        auto id = map.box_id[space];
        auto pos = map.id_box[id];
        boxes_to_move.insert(id);
        spaces_to_check.push(pos[0] + move);
        spaces_to_check.push(pos[1] + move);
      } else if (is_wall(space)) {
        // if we hit a wall ANYWHERE its done, nothing moves
        return;
      }
    }

    auto box_id_old = map.box_id;
    auto id_box_old = map.id_box;

    // first clean up
    for (auto box : boxes_to_move) {
      auto pos = map.id_box[box];
      map.box_id.erase(pos[0]);
      map.box_id.erase(pos[1]);
    }

    // then move
    for (auto box : boxes_to_move) {
      auto pos = id_box_old[box];
      pos[0] += move;
      pos[1] += move;
      map.id_box[box] = pos;
      map.box_id[pos[0]] = box;
      map.box_id[pos[1]] = box;
    }

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

std::string Day15_2(std::ifstream& in) {
  auto [map, moves] = ParseInputPart2(in);
  for (const auto& move : moves) {
    MovePart2(map, move);
  }
  int score = 0;
  for (const auto& box : map.id_box) {
    if (box.second[0] < box.second[1]) {
      score += box.second[0].x + 100 * box.second[0].y;
    } else {
      score += box.second[1].x + 100 * box.second[1].y;
    }
  }
  return std::to_string(score);
};