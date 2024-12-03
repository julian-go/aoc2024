#include <iostream>
#include <regex>
#include <sstream>

#include "solutions.hpp"

namespace {

template <bool kParseDos>
std::string Solve(std::ifstream& in) {
  std::stringstream ss{};
  ss << in.rdbuf();
  auto s = ss.str();

  std::regex regex(kParseDos ? R"r(mul\((\d+),(\d+)\)|do\(\)|don't\(\))r"
                             : R"r(mul\((\d+),(\d+)\))r");
  std::smatch matches{};

  auto it{s.cbegin()};
  int sum{0};
  bool active{true};

  while (std::regex_search(it, s.cend(), matches, regex)) {
    if constexpr (kParseDos) {
      if (matches[0] == "do()") {
        active = true;
      } else if (matches[0] == "don't()") {
        active = false;
      } else if (active) {
        sum += std::stoi(matches[1]) * std::stoi(matches[2]);
      }
    } else {
      sum += std::stoi(matches[1]) * std::stoi(matches[2]);
    }
    it = matches[0].second;  // Update to the end of the last match
  }

  return std::to_string(sum);
}

}  // namespace

std::string Day03_1(std::ifstream& in) { return Solve<false>(in); };

std::string Day03_2(std::ifstream& in) { return Solve<true>(in); };