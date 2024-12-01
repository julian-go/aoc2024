#ifndef AOC_UTILS_RUN_H_
#define AOC_UTILS_RUN_H_

#include <string>

#include "benchmark.hpp"
#include "problem.hpp"

namespace aoc {

struct Run {
  Problem problem;
  Benchmark benchmark;
  std::string solution;
};

}  // namespace aoc

#endif  // AOC_UTILS_RUN_H_