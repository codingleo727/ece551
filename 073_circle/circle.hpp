#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
  private:
    Point c;
    const double r;
  public:
    Circle(const Point & p, const double r): c(p), r(r) {}
    void move(double dx, double dy);
    double intersectionArea(const Circle & otherCircle);
};

#endif
