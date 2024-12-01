#ifndef AOC_UTILS_RUNNER_H_
#define AOC_UTILS_RUNNER_H_

#include <vector>

#include "problem.hpp"

namespace aoc {

class Runner {
 public:
  Runner(std::vector<Problem> problems, int num_runs)
      : problems{problems}, num_runs_{num_runs} {}
  ~Runner() = default;

  void Run();

 private:
  std::vector<Problem> problems;
  int num_runs_;
};

}  // namespace aoc

#endif  // AOC_UTILS_RUNNER_H_