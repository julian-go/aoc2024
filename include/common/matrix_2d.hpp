#ifndef MATRIX_2D_H_
#define MATRIX_2D_H_

#include <cstdint>
#include <ostream>
#include <type_traits>
#include <vector>

#include "common/vector_2d.hpp"

namespace aoc {

template <typename TType, bool TRowMajor = true>
class Matrix2D {
 public:
  Matrix2D() : size_x_(0), size_y_(0) {}
  Matrix2D(size_t size_x, size_t size_y) { resize(size_x, size_y); }
  Matrix2D(size_t size_x, size_t size_y, const TType& initial) {
    resize(size_x, size_y);
    fill(initial);
  }
  ~Matrix2D() = default;

  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  T& at(const Vector2D<int>& v) {
    return at(v.x, v.y);
  }

  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  T& at(const size_t& x, const size_t& y) {
    return data_[index(x, y)];
  }

  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  const TType& at(const Vector2D<int>& v) const {
    return at(v.x, v.y);
  }

  template <typename T = TType, typename std::enable_if_t<!std::is_same_v<T, bool>>* = nullptr>
  const TType& at(const size_t& x, const size_t& y) const {
    return data_[index(x, y)];
  }

  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  T at(const Vector2D<int>& v) const {
    return data_[index(v.x, v.y)];
  }

  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  T at(const size_t& x, const size_t& y) const {
    return data_[index(x, y)];
  }

  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  void set(const Vector2D<int>& v, T value) {
    data_[index(v.x, v.y)] = value;
  }

  template <typename T = TType, typename std::enable_if_t<std::is_same_v<T, bool>>* = nullptr>
  void set(const size_t& x, const size_t& y, T value) {
    data_[index(x, y)] = value;
  }

  void resize(const size_t& size_x, const size_t& size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
    data_.resize(size_x * size_y);
  }

  bool contains(const Vector2D<int>& v) const { return contains(v.x, v.y); }

  bool contains(const int& x, const int& y) const {
    return x >= 0 && y >= 0 && x < size_x_ && y < size_y_;
  }

  void fill(const TType& value) {
    for (size_t i = 0; i < data_.size(); ++i) {
      data_[i] = value;
    }
  }

  size_t sizeX() const { return size_x_; }
  size_t sizeY() const { return size_y_; }

  const std::vector<TType>& data() const { return data_; }

 private:
  std::vector<TType> data_;
  size_t size_x_;
  size_t size_y_;

  size_t index(const size_t& x, const size_t& y) const {
    if (TRowMajor) {
      return y * size_x_ + x;
    } else {
      return x * size_y_ + y;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Matrix2D& m) {
    for (size_t y = 0; y < m.size_y_; ++y) {
      for (size_t x = 0; x < m.size_x_; ++x) {
        out << m.at(x, y) << " ";
      }
      out << std::endl;
    }
    return out;
  }
};

}  // namespace aoc

#endif  // !MATRIX_2D_H_
