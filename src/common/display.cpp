#include "common/display.hpp"

#include <format>
#include <iostream>
#include <string>

namespace aoc {

void PrintDivider() {
  constexpr std::string_view d =
      "+{0:->18}+{0:->24}+{0:->6}+{0:->12}+{0:->12}+{0:->12}+{0:->12}+";
  std::cout << std::format(d, "") << std::endl;
}

void PrintHeader() {
  constexpr const char *header_row =
      "| {:^16} | {:^22} | {:^4} | {:^10} | {:^10} | {:^10} | {:^10} |";
  PrintDivider();
  std::cout << std::format(header_row, "Problem", "Solution", "Fail",
                           "Mean [us]", "STD [us]", "Min [us]", "Max [us]")
            << std::endl;
  PrintDivider();
}

void PrintRun(Run r) {
  constexpr const char *table_row =
      "| {:<16} | {:<22} | {:^4} | {:>10.0f} | {:>10.0f} | {:>10} | {:>10} |";
  std::cout << std::format(table_row, r.problem.label, r.solution,
                           r.problem.expected_result == r.solution ? "" : "x",
                           r.benchmark.mean_us,
                           r.benchmark.standard_deviation_us,
                           r.benchmark.minimum_us, r.benchmark.maximum_us)
            << std::endl;
}

}  // namespace aoc