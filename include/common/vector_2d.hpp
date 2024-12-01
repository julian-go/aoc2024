#ifndef AOC_COMMON_VECTOR_2D_H_
#define AOC_COMMON_VECTOR_2D_H_

#include <array>
#include <cstdint>
#include <iostream>

namespace aoc {

template <typename T = int, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
struct Vector2D {
  struct Hash {
    template <typename std::enable_if_t<std::is_same_v<T, int>>* = nullptr>
    std::size_t operator()(const Vector2D& v) const {
      return static_cast<std::uint64_t>(v.x) << 32 | static_cast<std::uint64_t>(v.y);
    }
  };

  constexpr Vector2D() : x(0), y(0){};
  constexpr Vector2D(T x, T y) : x(x), y(y){};
  constexpr virtual ~Vector2D() = default;

  T length() const { return std::abs(x) + std::abs(y); }
  T manhattan() const { return std::abs(x) + std::abs(y); }

  void RotateRight() {
    T tmp = x;
    x = -y;
    y = tmp;
  }

  void RotateLeft() {
    T tmp = x;
    x = y;
    y = -tmp;
  }

  Vector2D Right() { return {-y, x}; }
  Vector2D Left() { return {y, -x}; }

  auto Neighbors() const -> std::array<Vector2D, 4> { return {North(), South(), East(), West()}; }
  Vector2D North() const { return *this + Vector2D(0, -1); }
  Vector2D South() const { return *this + Vector2D(0, 1); }
  Vector2D East() const { return *this + Vector2D(1, 0); }
  Vector2D West() const { return *this + Vector2D(-1, 0); }

  Vector2D operator*(const int& r) const { return Vector2D(x * r, y * r); }

  Vector2D operator+(const Vector2D& r) const { return Vector2D(x + r.x, y + r.y); }

  Vector2D& operator+=(const Vector2D& r) {
    x += r.x;
    y += r.y;
    return *this;
  }

  Vector2D operator-(const Vector2D& r) const { return Vector2D(x - r.x, y - r.y); }

  inline bool operator==(const Vector2D& r) const { return x == r.x && y == r.y; }

  inline bool operator<(const Vector2D& r) const {
    if (x < r.x) {
      return true;
    } else if (x == r.x) {
      return y < r.y;
    } else {
      return false;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
    out << "(" << v.x << "," << v.y << ")";
    return out;
  }

  T x;
  T y;
};

template <typename T = int, std::enable_if<std::is_integral_v<T>>* = nullptr>
inline auto Manhattan(Vector2D<T> v1, Vector2D<T> v2) -> T {
  return (v1 - v2).length();
}

}  // namespace aoc

#endif  // !AOC_COMMON_VECTOR_2D_H_