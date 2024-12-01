#ifndef AOC_UTILS_BENCHMARK_H_
#define AOC_UTILS_BENCHMARK_H_

#include <cstdint>
#include <limits>

namespace aoc {

struct Benchmark {
  double mean_us = 0;
  double standard_deviation_us = 0;
  int64_t minimum_us = std::numeric_limits<int64_t>::max();
  int64_t maximum_us = std::numeric_limits<int64_t>::min();
};

}  // namespace aoc

#endif  // AOC_UTILS_BENCHMARK_H_