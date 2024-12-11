#include <cstdint>
#include <iostream>
#include <map>

#include "solutions.hpp"

namespace {

inline int NumberOfDigits(std::int64_t i) {
  // somehow faster than log10
  int n = 1;
  while (i >= 10) {
    i = i / 10;
    n++;
  }
  return n;
}

inline std::int64_t Pow10(int n) {
  std::int64_t result = 10;
  for (int i = 1; i < n; ++i) {
    result *= 10;
  }
  return result;
}

template <int kNumIterations>
std::string Solve(std::ifstream& in) {
  std::map<std::int64_t, std::int64_t> stones;
  std::int64_t token;
  while (in >> token) {
    stones[token] = 1;
  }

  auto AddStone = [](auto& stones, auto number, auto amount) {
    if (stones.contains(number)) {
      stones[number] += amount;
    } else {
      stones[number] = amount;
    }
  };

  for (int i = 0; i < kNumIterations; ++i) {
    std::map<std::int64_t, std::int64_t> new_stones;
    for (const auto& stone : stones) {
      std::int64_t number = stone.first;
      int num_digits = NumberOfDigits(number);
      if (number == 0) {
        AddStone(new_stones, 1, stone.second);
      } else if (num_digits % 2 == 0) {
        int N = Pow10(num_digits / 2);
        std::int64_t lhs = number / N;
        std::int64_t rhs = number % N;

        AddStone(new_stones, lhs, stone.second);
        AddStone(new_stones, rhs, stone.second);
      } else {
        AddStone(new_stones, number * 2024, stone.second);
      }
    }
    stones = new_stones;
  }

  std::int64_t count{0};
  for (const auto& stone : stones) {
    count += stone.second;
  }
  return std::to_string(count);
}

}  // namespace

std::string Day11_1(std::ifstream& in) { return Solve<25>(in); }

std::string Day11_2(std::ifstream& in) { return Solve<75>(in); }