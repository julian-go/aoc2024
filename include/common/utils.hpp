#ifndef AOC_COMMON_UTILS_H_
#define AOC_COMMON_UTILS_H_

#include <deque>
#include <fstream>
#include <string>

namespace aoc {

template <typename Iter>
int find_pattern_size(Iter from, Iter to, const int min_pattern_length) {
  if (std::distance(from, to) < 2 * min_pattern_length) {
    return 0;
  }

  const auto pat_2nd_start = from + min_pattern_length;
  const auto pat_2nd_end = to - min_pattern_length;

  int pattern_length{0};
  for (auto pat_2nd_begin = pat_2nd_start; pat_2nd_begin != pat_2nd_end; pat_2nd_begin++) {
    bool pattern_found{true};
    for (auto pat_1st = from, pat_2nd = pat_2nd_begin; pat_1st != pat_2nd_begin && pattern_found;
         ++pat_1st, ++pat_2nd) {
      if (pat_2nd == to) {
        pattern_found = false;
        break;
      }
      pattern_found = (*pat_1st == *pat_2nd);
    }
    if (pattern_found) {
      pattern_length = std::distance(from, pat_2nd_begin);
    }
  }
  return pattern_length;
}

inline auto size(std::ifstream& in) -> std::tuple<int, int> {
  auto line = std::string{};
  int x{0};
  int y{0};
  while (std::getline(in, line)) {
    if (x == 0) {
      x = std::ssize(line);
    }
    ++y;
  }
  // rewind stream
  in.clear();
  in.seekg(0, std::ios::beg);
  return {x, y};
}

}  // namespace aoc

#endif  // !AOC_COMMON_UTILS_H_