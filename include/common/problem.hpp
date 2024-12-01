#ifndef AOC_UTILS_PROBLEM_H_
#define AOC_UTILS_PROBLEM_H_

#include <cstdint>
#include <fstream>
#include <functional>
#include <string>

namespace aoc {

using solver_t = std::function<std::string(std::ifstream&)>;

struct Problem {
  std::string label;
  solver_t solve;
  std::string expected_result;
  std::string input_file_path;
};

}  // namespace aoc

#endif  // AOC_UTILS_PROBLEM_H_