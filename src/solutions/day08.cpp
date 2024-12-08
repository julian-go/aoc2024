#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

using Vector = aoc::Vector2D<int>;

void PrintAntinodes(const std::unordered_set<Vector, Vector::Hash>& antinodes, Vector map_size) {
  for (int y = 0; y < map_size.y; ++y) {
    for (int x = 0; x < map_size.x; ++x) {
      if (antinodes.contains({x, y})) {
        std::cout << '#';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}

auto ParseInput(std::ifstream& in) {
  std::string line{};
  in >> line;
  Vector map_size(std::ssize(line), std::ssize(line));
  std::unordered_map<char, std::vector<Vector>> towers;
  int y{0};
  do {
    int x{0};
    for (const auto& c : line) {
      if (c != '.') {
        if (towers.contains(c)) {
          towers[c].push_back({x, y});
        } else {
          towers[c] = {{x, y}};
        }
      }
      ++x;
    }
    ++y;
  } while (in >> line);
  return std::tuple{map_size, towers};
}

template <int part>
std::string Solve(std::ifstream& in) {
  auto [map_size, towers] = ParseInput(in);
  std::unordered_set<Vector, Vector::Hash> antinodes;
  auto location_valid = [&map_size](auto v) {
    return v.x >= 0 && v.x < map_size.x && v.y >= 0 && v.y < map_size.y;
  };
  for (const auto& pairs : towers) {
    for (auto lhs = pairs.second.begin(); lhs != pairs.second.end(); ++lhs) {
      for (auto rhs = lhs + 1; rhs != pairs.second.end(); ++rhs) {
        auto dx = rhs->x - lhs->x;
        auto dy = rhs->y - lhs->y;

        if constexpr (part == 1) {
          // -- PART 1 --
          // Part one just considers the first harmonic
          Vector antinode{lhs->x - dx, lhs->y - dy};
          if (location_valid(antinode)) {
            antinodes.insert(antinode);
          }

          antinode = {rhs->x + dx, rhs->y + dy};
          if (location_valid(antinode)) {
            antinodes.insert(antinode);
          }
        } else {
          // -- PART 2 --
          // Part two adds the tower itself and then loops in either direction until it falls off
          // the map
          antinodes.emplace(lhs->x, lhs->y);
          Vector antinode{lhs->x - dx, lhs->y - dy};
          while (location_valid(antinode)) {
            antinodes.insert(antinode);
            antinode -= {dx, dy};
          }

          antinodes.emplace(rhs->x, rhs->y);
          antinode = {rhs->x + dx, rhs->y + dy};
          while (location_valid(antinode)) {
            antinodes.insert(antinode);
            antinode += {dx, dy};
          }
        }
      }
    }
  }
  return std::to_string(std::ssize(antinodes));
}

}  // namespace

std::string Day08_1(std::ifstream& in) { return Solve<1>(in); };

std::string Day08_2(std::ifstream& in) { return Solve<2>(in); };