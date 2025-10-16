#include "circle.hpp"

#include <cmath>
#include <cstdio>

void Circle::move(double dx, double dy) {
  c.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = c.distanceFrom(otherCircle.c);
  double sum_radii = r + otherCircle.r;
  if (d > sum_radii) {
    return 0;
  }
  
  double diff_radii = std::abs(r - otherCircle. r);
  if (d <= diff_radii && otherCircle.r <=  r) {
    return M_PI * otherCircle. r * otherCircle. r;
  }
  else if (d <= diff_radii && r <= otherCircle.r) {
    return M_PI * r * r;
  }
  else {
    double a1 = (r * r) * std::acos((d * d + r * r - otherCircle.r * otherCircle.r) / (2 * d * r));
    double a2 = (otherCircle.r * otherCircle.r) * std::acos((d * d + otherCircle.r * otherCircle.r - r * r) / (2 * d * otherCircle.r));
    double a3 = 0.5 * std::sqrt((r + otherCircle.r - d) * (d + r - otherCircle.r) * (d - r + otherCircle.r) * (d + r + otherCircle.r));
    double final_sum = a1 + a2 - a3;
    return final_sum;
  }
  return 0;
}
