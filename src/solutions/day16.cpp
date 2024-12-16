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

auto ParseInput(std::ifstream& in) {
  std::string line{};
  std::getline(in, line);
  auto map = Map(line.size(), line.size());
  Vector start, stop;

  int y = 0;
  do {
    int x = 0;
    for (const auto& c : line) {
      map.at(x, y) = c;
      if (c == 'S') {
        start = {x, y};
      } else if (c == 'E') {
        stop = {x, y};
      }
      x++;
    }
    y++;
  } while (std::getline(in, line));

  return std::tuple{map, start, stop};
}

struct State {
  State() {};
  State(Vector p, Vector o) : position{p}, orientation{o} {};
  struct Hash {
    std::size_t operator()(const State& s) const {
      return (static_cast<std::uint64_t>(s.position.x) << 32 |
              static_cast<std::uint64_t>(s.position.y)) ^
             (static_cast<std::uint64_t>(s.orientation.x) << 32 |
              static_cast<std::uint64_t>(s.orientation.y));
    }
  };
  Vector position{};
  Vector orientation{};

  bool operator==(const State& other) const {
    return position == other.position && orientation == other.orientation;
  }
};

struct Node {
  State state{};
  std::vector<State> parents{};
  std::unordered_set<Vector, Vector::Hash> neighbors{};
  int distance{1000000};

  bool operator<(const Node& other) const { return distance > other.distance; }
};

const std::vector<Vector> kOrientations = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

}  // namespace

std::string Day16_1(std::ifstream& in) {
  auto [map, start, stop] = ParseInput(in);

  // First naively build the graph
  std::unordered_map<State, Node, State::Hash> graph;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeY(); ++x) {
      if (map.at(x, y) != '#') {
        Node node;
        node.state.position = {x, y};
        for (auto o : kOrientations) {
          node.state.orientation = o;
          for (auto n : Vector(x, y).Neighbors()) {
            if (map.at(n) != '#') {
              node.neighbors.insert(n);
            }
          }
          graph[node.state] = node;
        }
      }
    }
  }

  std::priority_queue<Node> queue;

  State start_node{start, {1, 0}};
  State goal_node{};
  graph[start_node].distance = 0;
  queue.push(graph[start_node]);

  std::unordered_set<State, State::Hash> visited;

  int cost = 1e7;
  while (!queue.empty()) {
    auto node = queue.top();
    queue.pop();
    if (node.state.position == stop) {
      if (node.distance < cost) {
        cost = node.distance;
        goal_node = node.state;
      }
    } else {
      auto straight = node.state.position + node.state.orientation;
      auto left = node.state.position + node.state.orientation.Left();
      auto right = node.state.position + node.state.orientation.Right();

      if (node.neighbors.contains(straight)) {
        auto new_state = State{straight, node.state.orientation};
        auto new_distance = node.distance + 1;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }

        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }

      if (node.neighbors.contains(left)) {
        auto new_state = State{left, node.state.orientation.Left()};
        auto new_distance = node.distance + 1001;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }
        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }

      if (node.neighbors.contains(right)) {
        auto new_state = State{right, node.state.orientation.Right()};
        auto new_distance = node.distance + 1001;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }
        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }
    }
  }

  std::queue<State> goal_nodes;
  goal_nodes.push(goal_node);
  while (!goal_nodes.empty()) {
    auto current = goal_nodes.front();
    goal_nodes.pop();
    map.at(current.position) = 'O';
    for (auto p : graph[current].parents) {
      goal_nodes.push(p);
    }
  }

  // std::cout << map;

  return std::to_string(cost);
};

std::string Day16_2(std::ifstream& in) {
  auto [map, start, stop] = ParseInput(in);

  // First naively build the graph
  std::unordered_map<State, Node, State::Hash> graph;
  for (int y = 0; y < map.sizeY(); ++y) {
    for (int x = 0; x < map.sizeY(); ++x) {
      if (map.at(x, y) != '#') {
        Node node;
        node.state.position = {x, y};
        for (auto o : kOrientations) {
          node.state.orientation = o;
          for (auto n : Vector(x, y).Neighbors()) {
            if (map.at(n) != '#') {
              node.neighbors.insert(n);
            }
          }
          graph[node.state] = node;
        }
      }
    }
  }

  std::priority_queue<Node> queue;

  State start_node{start, {1, 0}};
  State goal_node{};
  graph[start_node].distance = 0;
  queue.push(graph[start_node]);

  std::unordered_set<State, State::Hash> visited;

  int cost = 1e7;
  while (!queue.empty()) {
    auto node = queue.top();
    queue.pop();
    if (node.state.position == stop) {
      if (node.distance < cost) {
        cost = node.distance;
        goal_node = node.state;
      }
    } else {
      auto straight = node.state.position + node.state.orientation;
      auto left = node.state.position + node.state.orientation.Left();
      auto right = node.state.position + node.state.orientation.Right();

      if (node.neighbors.contains(straight)) {
        auto new_state = State{straight, node.state.orientation};
        auto new_distance = node.distance + 1;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }

        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }

      if (node.neighbors.contains(left)) {
        auto new_state = State{left, node.state.orientation.Left()};
        auto new_distance = node.distance + 1001;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }
        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }

      if (node.neighbors.contains(right)) {
        auto new_state = State{right, node.state.orientation.Right()};
        auto new_distance = node.distance + 1001;
        if (new_distance <= graph[new_state].distance) {
          graph[new_state].distance = new_distance;
          if (new_distance == graph[new_state].distance) {
            graph[new_state].parents.push_back(node.state);
          } else {
            graph[new_state].parents = {node.state};
          }
        }
        if (!visited.contains(new_state)) {
          visited.insert(new_state);
          queue.push(graph[new_state]);
        }
      }
    }
  }

  std::queue<State> goal_nodes;
  goal_nodes.push(goal_node);
  while (!goal_nodes.empty()) {
    auto current = goal_nodes.front();
    goal_nodes.pop();
    map.at(current.position) = 'O';
    for (auto p : graph[current].parents) {
      goal_nodes.push(p);
    }
  }

  int num = std::count(map.data().begin(), map.data().end(), 'O');

  return std::to_string(num);
};