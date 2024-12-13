#include <array>
#include <iostream>
#include <sstream>

#include "solutions.hpp"

namespace {
using int_t = std::int64_t;

struct ClawMachine {
  std::array<int_t, 2> button_a{};
  std::array<int_t, 2> button_b{};
  std::array<int_t, 2> target{};
};

std::vector<ClawMachine> ParseInput(std::ifstream& in) {
  std::string line{};
  std::vector<ClawMachine> machines;
  do {
    machines.emplace_back();
    {
      std::getline(in, line);
      std::stringstream ss{line};
      int_t token{0};

      ss.ignore(12);
      ss >> token;
      machines.back().button_a[0] = token;

      ss.ignore(4);
      ss >> token;
      machines.back().button_a[1] = token;
    }
    {
      std::getline(in, line);
      std::stringstream ss{line};
      int_t token{0};

      ss.ignore(12);
      ss >> token;
      machines.back().button_b[0] = token;

      ss.ignore(4);
      ss >> token;
      machines.back().button_b[1] = token;
    }
    {
      std::getline(in, line);
      std::stringstream ss{line};
      int_t token{0};

      ss.ignore(9);
      ss >> token;
      machines.back().target[0] = token;

      ss.ignore(4);
      ss >> token;
      machines.back().target[1] = token;
    }
    // skip empty line
  } while (std::getline(in, line));

  return machines;
}

template <bool part2>
int_t Solve(const ClawMachine& machine) {
  // Simply solve using the inverse matrix
  constexpr std::int64_t kPart2Scale = 10'000'000'000'000;
  const int_t a = machine.button_a[0];
  const int_t b = machine.button_b[0];
  const int_t c = machine.button_a[1];
  const int_t d = machine.button_b[1];

  int_t y_1 = machine.target[0];
  int_t y_2 = machine.target[1];

  if constexpr (part2) {
    y_1 += kPart2Scale;
    y_2 += kPart2Scale;
  }

  double determinant = a * d - b * c;

  // the determinant does not seem to ever be zero, so we dont check it here
  const int_t x_1 = static_cast<int_t>(round(1 / determinant * (d * y_1 - b * y_2)));
  const int_t x_2 = static_cast<int_t>(round(1 / determinant * (-c * y_1 + a * y_2)));

  // I considered checking the int-ness of x_1 and x_2 before, but all the edge cases gave me
  // headaches, this check is more reliable and just works
  const int_t y_1_hat = round(machine.button_a[0] * x_1 + machine.button_b[0] * x_2);
  const int_t y_2_hat = round(machine.button_a[1] * x_1 + machine.button_b[1] * x_2);
  if (y_1 != y_1_hat || y_2 != y_2_hat) {
    return 0;
  }

  return 3 * x_1 + x_2;
}
}  // namespace

std::string Day13_1(std::ifstream& in) {
  auto machines = ParseInput(in);
  int_t result{0};
  for (const auto& machine : machines) {
    result += Solve<false>(machine);
  }
  return std::to_string(result);
};

std::string Day13_2(std::ifstream& in) {
  auto machines = ParseInput(in);
  int_t result{0};
  for (const auto& machine : machines) {
    result += Solve<true>(machine);
  }
  return std::to_string(result);
  ;
};