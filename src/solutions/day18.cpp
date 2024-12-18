#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "common/matrix_2d.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"
namespace {
using Vector = aoc::Vector2D<int>;
using Map = aoc::Matrix2D<char>;

auto ParseInputPart1(std::ifstream& in) {
  int n = 12;

  std::unordered_set<Vector, Vector::Hash> obstacles;

  for (int i = 0; i < 12; ++i) {
    Vector c;
    in >> c.x;
    in.ignore(1);
    in >> c.y;
    obstacles.insert(c);
  }

  return std::tuple{obstacles};
}

struct Node {
  Vector position{};
  int distance{1000000};

  bool operator<(const Node& other) const { return distance > other.distance; }
};

}  // namespace
std::string Day18_1(std::ifstream& in) {
  int N = 6;
  auto obstacles = ParseInputPart1(in);
  auto start = Vector(0, 0);
  auto goal = Vector(6, 6);

  std::priority_queue<Node> queue;
  std::unordered_set<Vector, Vector::Hash> visited;
  std::unordered_map<Vector, Node, Vector::Hash> graph;

  {
    Node n;
    n.position = start;
    n.distance = 0;
    queue.push(n);
    graph[start] = n;
  }

  int cost = 1000000;
  auto valid = []() {};

  while (!queue.empty()) {
    auto cur = queue.top();
    queue.pop();
    if (cur.position == goal) {
      if (cur.distance < cost) {
        cost = cur.distance;
      }
    } else {
    }
  }

  return "";
};

std::string Day18_2(std::ifstream& in) { return ""; };