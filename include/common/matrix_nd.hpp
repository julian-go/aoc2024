#ifndef AOC_COMMON_MATRIX_ND_H_
#define AOC_COMMON_MATRIX_ND_H_

#include <array>
#include <cassert>
#include <cstdint>
#include <ostream>
#include <type_traits>
#include <vector>

#include "common/vector_2d.hpp"

namespace aoc {

template <typename TType, int Dims>
class Matrix {
 public:
  // numer of strides must be equal to number of dimensions and is given in the constructor
  template <typename... TArgs>
  Matrix(TArgs... args) : dims_(args...) {
    static_assert(sizeof...(args) == Dims,
                  "Matrix: Number of arguments in constructor must match number of dimensions");
    // check that args are integer types
    static_assert((std::is_integral_v<TArgs> && ...),
                  "Matrix: All arguments in constructor must be integer types");
    // If strides the dimensions are [10, 5, 2, 4] then the strides are [1, 10, 50, 100]
    strides_[0] = 1;
    for (int i = 0; i < Dims - 1; ++i) {
      strides_[i + 1] = strides_[i] * dims_[i];
    }
    data_.resize(strides_.back() * dims_.back());
  }

  bool contains(Vector2D<int> v) const {
    static_assert(Dims == 2, "Matrix: Number of arguments for index must be two");
    return contains(v.x, v.y);
  }

  template <typename... TArgs>
  bool contains(TArgs... args) const {
    static_assert(sizeof...(args) == Dims,
                  "Matrix: Number of arguments for index must match number of dimensions");
    return contains_impl(args...);
  }

  void fill(TType value) { std::fill(data_.begin(), data_.end(), value); }

  const std::array<int, Dims>& size() const { return dims_; }

  int size(int dim) const {
    assert(dim < Dims);
    return dims_[dim];
  }

  // Non-boolean types
  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  T& at(Vector2D<int> v) {
    static_assert(Dims == 2, "Matrix: Number of arguments for index must be two");
    return at(v.x, v.y);
  }

  template <typename T = TType, typename... TArgs,
            typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  T& at(TArgs... args) {
    return data_[index(args...)];
  }

  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  const T& at(Vector2D<int> v) const {
    static_assert(Dims == 2, "Matrix: Number of arguments for index must be two");
    return at(v.x, v.y);
  }

  template <typename T = TType, typename... TArgs,
            typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  const T& at(TArgs... args) const {
    return data_[index(args...)];
  }

  // Boolean specialization
  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  T at(Vector2D<int> v) const {
    static_assert(Dims == 2, "Matrix: Number of arguments for index must be two");
    return at(v.x, v.y);
  }

  template <typename T = TType, typename... TArgs,
            typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  T at(TArgs... args) const {
    static_assert(sizeof...(args) == Dims,
                  "Matrix: Number of arguments for index must match number of dimensions");
    return data_[index(args...)];
  }

  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  void set(T value, Vector2D<int> v) {
    static_assert(Dims == 2,
                  "Matrix: Number of arguments for index must match number of dimensions");
    set(value, v.x, v.y);
  }

  template <typename T = TType, typename... TArgs,
            typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  void set(T value, TArgs... args) {
    static_assert(sizeof...(args) == Dims,
                  "Matrix: Number of arguments for index must match number of dimensions");
    data_[index(args...)] = value;
  }

  std::vector<TType>& get() { return data_; }
  const std::vector<TType>& get() const { return data_; }

 private:
  std::vector<TType> data_;
  std::array<int, Dims> strides_;
  std::array<int, Dims> dims_;

  template <typename... TArgs>
  int index(TArgs... args) const {
    static_assert(sizeof...(args) == Dims,
                  "Matrix: Number of arguments for index must match number of dimensions");
    return index_impl(args...);
  }

  template <typename... TArgs>
  int index_impl(int arg, TArgs... args) const {
    return arg * strides_[Dims - sizeof...(args) - 1] + index_impl(args...);
  }

  int index_impl(int arg) const { return arg * strides_.back(); }

  template <typename... TArgs>
  bool contains_impl(int arg, TArgs... args) const {
    return arg >= 0 && arg < dims_[Dims - sizeof...(args) - 1] && contains_impl(args...);
  }

  bool contains_impl(int arg) const { return arg >= 0 && arg < dims_.back(); }
};

}  // namespace aoc

#endif  // !AOC_COMMON_MATRIX_ND_H_
