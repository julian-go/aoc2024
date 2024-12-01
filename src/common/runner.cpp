#include "common/runner.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>

#include "common/benchmark.hpp"
#include "common/display.hpp"
#include "common/run.hpp"

namespace aoc {

void Runner::Run() {
  using namespace std::chrono;

  PrintHeader();

  for (const auto& problem : problems) {
    auto start = high_resolution_clock::time_point{};
    auto b = Benchmark{};
    auto old_mean = double{0};
    auto variance = double{0};
    auto result = std::string{};
    for (int i{0}; i < num_runs_; ++i) {
      auto input_file = std::ifstream{problem.input_file_path};
      start = high_resolution_clock::now();
      result = problem.solve(input_file);
      auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start).count();

      b.maximum_us = std::max(b.maximum_us, elapsed);
      b.minimum_us = std::min(b.minimum_us, elapsed);
      int n = i + 1;
      old_mean = b.mean_us;
      b.mean_us += (static_cast<double>(elapsed) - b.mean_us) / n;
      variance = variance + ((elapsed - b.mean_us) * (elapsed - old_mean) - variance) / n;
    }
    b.standard_deviation_us = std::sqrt(variance);
    PrintRun(aoc::Run{problem, b, result});
  }

  PrintDivider();
}

}  // namespace aoc