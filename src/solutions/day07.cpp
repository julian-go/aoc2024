#include <cstdint>
#include <iostream>
#include <sstream>

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
  int result = 10;
  for (int i = 1; i < n; ++i) {
    result *= 10;
  }
  return result;
}

template <int part>
bool f(const std::int64_t& result, const std::vector<std::int64_t>& elements, int next_element,
       std::int64_t interim_result) {
  // We have reached the end, the result is whatever the saved interim result is.
  if (next_element == std::ssize(elements)) {
    return interim_result == result;
  }

  // It is no longer possible, since we only increase the interim
  if (interim_result > result) {
    return false;
  }

  if constexpr (part == 1) {
    return f<part>(result, elements, next_element + 1, interim_result + elements[next_element]) ||
           f<part>(result, elements, next_element + 1, interim_result * elements[next_element]);
  } else {
    return f<part>(result, elements, next_element + 1, interim_result + elements[next_element]) ||
           f<part>(result, elements, next_element + 1, interim_result * elements[next_element]) ||
           f<part>(result, elements, next_element + 1,
                   interim_result * Pow10(NumberOfDigits(elements[next_element])) +
                       elements[next_element]);
  }
}

template <int part>
std::string Solve(std::ifstream& in) {
  std::string line{};
  std::int64_t calibration_value{0};

  while (std::getline(in, line)) {
    std::stringstream ss{line};
    std::int64_t result;
    std::int64_t element;
    std::vector<std::int64_t> elements;

    ss >> result;
    ss.ignore(1);
    while (ss >> element) {
      elements.push_back(element);
    }

    if (f<part>(result, elements, 1, elements.front())) {
      calibration_value += result;
    }
  }
  return std::to_string(calibration_value);
}

}  // namespace

std::string Day07_1(std::ifstream& in) { return Solve<1>(in); };

std::string Day07_2(std::ifstream& in) { return Solve<2>(in); };