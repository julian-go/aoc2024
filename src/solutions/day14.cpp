#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <thread>

#include "common/vector_2d.hpp"
#include "solutions.hpp"
namespace {

using Vector = aoc::Vector2D<int>;

struct Robot {
  Vector p;
  Vector v;
};

auto ParseInput(std::ifstream& in) {
  std::string line{};
  std::vector<Robot> robots;
  while (std::getline(in, line)) {
    std::stringstream ss{line};
    robots.emplace_back();
    ss.ignore(2);
    ss >> robots.back().p.x;
    ss.ignore(1);
    ss >> robots.back().p.y;
    ss.ignore(3);
    ss >> robots.back().v.x;
    ss.ignore(1);
    ss >> robots.back().v.y;
  }
  return robots;
}

int Wrap(int x, int w) {
  if (x < 0) {
    x += w * (-x / w + 1);
  }
  return x % w;
}

void Draw(const std::set<Vector>& robots) {
  for (int y = 0; y < 103; ++y) {
    for (int x = 0; x < 101; ++x) {
      if (robots.contains({x, y})) {
        std::cout << '#';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}

bool FindBlob(const std::set<Vector>& robots) {
  std::set<Vector> visited{};
  for (const auto& robot : robots) {
    if (visited.size() > robots.size() / 5) {
      // dodgy optimization
      return false;
    }
    if (!visited.contains(robot)) {
      visited.insert(robot);
      std::stack<Vector> to_visit;
      to_visit.push(robot);
      int blob = 0;
      while (!to_visit.empty()) {
        blob++;
        auto& current = to_visit.top();
        to_visit.pop();
        for (auto const& n : current.Neighbors()) {
          if (!visited.contains(n) && robots.contains(n)) {
            visited.insert(n);
            to_visit.push(n);
          }
        }
      }
      if (blob > 20) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace

std::string Day14_1(std::ifstream& in) {
  auto robots = ParseInput(in);
  Vector map_size{101, 103};
  if (std::ssize(robots) == 12) {
    map_size = {11, 7};
  }

  std::array<int, 4> quadrants{0};
  for (auto& robot : robots) {
    robot.p += robot.v * 100;
    robot.p.x = Wrap(robot.p.x, map_size.x);
    robot.p.y = Wrap(robot.p.y, map_size.y);
    if (robot.p.x < map_size.x / 2) {
      if (robot.p.y < map_size.y / 2) {
        quadrants[1]++;
      } else if (robot.p.y > map_size.y / 2) {
        quadrants[2]++;
      }
    } else if (robot.p.x > map_size.x / 2) {
      if (robot.p.y < map_size.y / 2) {
        quadrants[0]++;
      } else if (robot.p.y > map_size.y / 2) {
        quadrants[3]++;
      }
    }
  }

  return std::to_string(
      std::accumulate(quadrants.begin(), quadrants.end(), 1, std::multiplies<int>()));
};

std::string Day14_2(std::ifstream& in) {
  auto robots = ParseInput(in);
  Vector map_size{101, 103};
  if (std::ssize(robots) == 12) {
    return "n/a";
  }

  int seconds = 0;
  while (true) {
    ++seconds;
    std::set<Vector> drawing_set{};
    for (auto& robot : robots) {
      robot.p += robot.v;
      robot.p.x = Wrap(robot.p.x, map_size.x);
      robot.p.y = Wrap(robot.p.y, map_size.y);
      drawing_set.insert(robot.p);
    }
    // Just find a blob of at least 20 robots, then it should be an image
    if (FindBlob(drawing_set)) {
      break;
    }
  }
  return std::to_string(seconds);
};