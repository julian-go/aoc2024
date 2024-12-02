#include <functional>
#include <sstream>
#include <string>

#include "solutions.hpp"

namespace {

using Compare = std::function<bool(int, int)>;

inline auto kIncreasing = [](auto current, auto next) constexpr {
  return next > current && next - current <= 3;
};

inline auto kDecreasing = [](auto current, auto next) constexpr {
  return next < current && current - next <= 3;
};

bool CheckVector(const std::vector<int>& v, std::vector<int>::const_iterator drop, Compare pred) {
  auto current{v.begin()};
  auto next{v.begin() + 1};
  while (next != v.end()) {
    // If we drop one we need to do a bunch of checks to avoid out of bounds access
    if (next == drop) {
      ++next;
    } else if (current == drop) {
      ++current;
      if (current == next) {
        ++next;
      }
    }

    if (next != v.end()) {
      if (!pred(*current, *next)) {
        return false;
      }
      ++current;
      ++next;
    }
  }

  return true;
}

bool CheckPart1(const std::vector<int>& v) {
  return CheckVector(v, v.end(), kIncreasing) || CheckVector(v, v.end(), kDecreasing);
};

bool CheckPart2(const std::vector<int>& v) {
  for (auto drop = v.begin(); drop != v.end(); ++drop) {
    if (CheckVector(v, drop, kIncreasing) || CheckVector(v, drop, kDecreasing)) {
      return true;
    }
  }
  return false;
};

}  // namespace

std::string Day02_1(std::ifstream& in) {
  std::string line{};
  int num_safe{0}, token{0};
  while (std::getline(in, line)) {
    std::stringstream ss{line};
    std::vector<int> row{};
    while (ss >> token) {
      row.push_back(token);
    }
    if (CheckPart1(row)) {
      num_safe++;
    }
  }
  return std::to_string(num_safe);
};

std::string Day02_2(std::ifstream& in) {
  std::string line{};
  int num_safe{0}, token{0};
  while (std::getline(in, line)) {
    std::stringstream ss{line};
    std::vector<int> row{};
    while (ss >> token) {
      row.push_back(token);
    }
    if (CheckPart2(row)) {
      num_safe++;
    }
  }
  return std::to_string(num_safe);
};