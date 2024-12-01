#ifndef AOC_COMMON_INTERVAL_H_
#define AOC_COMMON_INTERVAL_H_

#include <cstdint>
#include <vector>

namespace aoc {

using int_t = std::int64_t;

// Interval [start, end)
struct Interval {
  int_t start;
  int_t end;

  int_t length() const { return end - start; }
  bool empty() const { return start == end; }

  Interval& operator+=(const int_t& offset) {
    start += offset;
    end += offset;
    return *this;
  }

  Interval& operator-=(const int_t& offset) {
	start -= offset;
	end -= offset;
	return *this;
  }

  bool operator<(const Interval& rhs) const { return start < rhs.start; }

  friend std::ostream& operator<<(std::ostream& out, const Interval& i) {
    return out << "[" << i.start << ", " << i.end << ")";
  }
};

Interval Union(const Interval& lhs, const Interval& rhs) {
  return Interval{std::min(lhs.start, rhs.start), std::max(lhs.end, rhs.end)};
}

Interval Intersection(const Interval& lhs, const Interval& rhs) {
  auto start = std::max(lhs.start, rhs.start);
  auto end = std::min(lhs.end, rhs.end);
  if (start >= end) {
    return Interval{start, start};
  } else {
    return Interval{std::max(lhs.start, rhs.start), std::min(lhs.end, rhs.end)};
  }
}

bool Contains(const Interval& lhs, const Interval& rhs) {
  return lhs.start <= rhs.start && lhs.end >= rhs.end;
}

std::vector<Interval> Difference(const Interval& lhs, const Interval& rhs) {
  if (lhs.start >= rhs.end || lhs.end <= rhs.start) {
    return {lhs};
  } else if (lhs.start < rhs.start && lhs.end > rhs.end) {
    return {Interval{lhs.start, rhs.start}, Interval{rhs.end, lhs.end}};
  } else if (lhs.start < rhs.start) {
    return {Interval{lhs.start, rhs.start}};
  } else if (lhs.end > rhs.end) {
    return {Interval{rhs.end, lhs.end}};
  } else {
    return {};
  }
}

}  // namespace aoc

#endif  // !AOC_COMMON_INTERVAL_H_
