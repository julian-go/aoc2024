#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "solutions.hpp"

namespace {

auto parse(std::ifstream& in) {
  int l, r;
  std::vector<int> list_l, list_r;
  while (in >> l >> r) {
    list_l.push_back(l);
    list_r.push_back(r);
  }
  return std::tuple{list_l, list_r};
}

}  // namespace

std::string Day01_1(std::ifstream& in) {
  auto [list_l, list_r] = parse(in);

  std::sort(list_l.begin(), list_l.end());
  std::sort(list_r.begin(), list_r.end());

  int sum{0};
  for (int i = 0; i < std::ssize(list_l); ++i) {
    sum += std::abs(list_l[i] - list_r[i]);
  }
  return std::to_string(sum);
};

std::string Day01_2(std::ifstream& in) {
  auto [list_l, list_r] = parse(in);

  // Cache a map of all appearances in the right list
  std::unordered_map<int, int> multiplicity{};
  for (const auto& value : list_r) {
    if (multiplicity.contains(value)) {
      multiplicity[value]++;
    } else {
      multiplicity[value] = 1;
    }
  }

  // Now we just compute the sum using the cached map
  int sum{0};
  for (const auto& value : list_l) {
    sum += value * multiplicity[value];
  }

  return std::to_string(sum);
};