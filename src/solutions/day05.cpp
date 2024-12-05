#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "solutions.hpp"

namespace {

auto ReadOrdering(std::ifstream& in) {
  std::string line{};
  std::unordered_map<int, std::set<int>> ordering;
  while (std::getline(in, line) && !line.empty()) {
    std::stringstream ss{line};
    int left, right;
    ss >> left;
    ss.ignore(1);
    ss >> right;
    ordering[left].insert(right);
  };
  return ordering;
}

template <int part>
std::string Solve(std::ifstream& in) {
  auto ordering = ReadOrdering(in);

  auto is_less = [&ordering](auto left, auto right) -> bool {
    auto pages_required_after = ordering[left];
    return pages_required_after.contains(right);
  };

  int sum{0};
  std::string line{};

  while (std::getline(in, line)) {
    std::stringstream ss{line};
    int valid{true};
    int page;
    std::vector<int> update;
    while (ss >> page) {
      update.push_back(page);
      ss.ignore(1);  // skip seperator
    }
    if (part == 1 && std::is_sorted(update.begin(), update.end(), is_less)) {
      // In part one we just sum the middle element of each valid update
      sum += update[std::ssize(update) / 2];
    } else if (part == 2 && !std::is_sorted(update.begin(), update.end(), is_less)) {
      // In part two we just sum the middle element of each invalid update AFTER sorting
      std::sort(update.begin(), update.end(), is_less);
      sum += update[std::ssize(update) / 2];
    }
  };

  return std::to_string(sum);
}

}  // namespace

std::string Day05_1(std::ifstream& in) { return Solve<1>(in); };

std::string Day05_2(std::ifstream& in) { return Solve<2>(in); };