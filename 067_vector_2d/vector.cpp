#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D result;
  result.initVector(x + rhs.x, y + rhs.y);
  return result;
}

double Vector2D::getMagnitude() const {
  return std::sqrt(x * x + y * y);
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
