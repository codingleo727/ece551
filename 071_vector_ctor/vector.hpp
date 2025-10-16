/* write your class interface in this file
   write function definitions only if they are very short
 */
#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
class Vector2D {
  private:
    double x;
    double y;

  public:
    Vector2D(): x(0), y(0) {};
    Vector2D(double x, double y): x(x), y(y){};
    double getMagnitude() const;
    Vector2D operator+(const Vector2D & rhs) const;
    Vector2D & operator+=(const Vector2D & rhs);
    double dot(const Vector2D & rhs) const {
      return (x * rhs.x) + (y * rhs.y);
    }
    void print() const;
};

#endif
