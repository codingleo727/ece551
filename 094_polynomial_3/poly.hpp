#ifndef POLY_HPP
#define POLY_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <exception>

template<typename NumT>
class convergence_failure : public std::exception {
public:
  const NumT value;

  explicit convergence_failure(NumT & v): value(v) {}

  virtual const char * what() const throw() {
    return "Convergence failure";
  }
};

template<typename NumT>
class Polynomial {
 private:
  std::vector<NumT> coefs;

  void normalize() {
    while (!coefs.empty() && coefs.back() == NumT()) {
      coefs.pop_back();
    }

    if (coefs.empty()) {
      coefs.push_back(NumT());
    }
  }

  bool isZero() const { return coefs.size() == 1 && coefs[0] == NumT(); }
 public:
  Polynomial() : coefs(1, NumT()) {}

  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial result;
    size_t size = std::max(coefs.size(), rhs.coefs.size());
    result.coefs.assign(size, NumT());
    for (size_t i = 0; i < size; i++) {
      NumT left = (i < coefs.size()) ? coefs[i] : NumT();
      NumT right = (i < rhs.coefs.size()) ? rhs.coefs[i] : NumT();
      result.coefs[i] = left + right;
    }

    result.normalize();

    return result;
  }

  Polynomial operator-() const {
    Polynomial result;
    result.coefs.resize(coefs.size(), NumT());
    for (size_t i = 0; i < coefs.size(); i++) {
      result.coefs[i] = NumT() - coefs[i];
    }

    result.normalize();

    return result;
  }

  Polynomial operator-(const Polynomial & rhs) const {
    Polynomial result;
    size_t size = std::max(coefs.size(), rhs.coefs.size());
    result.coefs.assign(size, NumT());
    for (size_t i = 0; i < size; i++) {
      NumT left = (i < coefs.size()) ? coefs[i] : NumT();
      NumT right = (i < rhs.coefs.size()) ? rhs.coefs[i] : NumT();
      result.coefs[i] = left - right;
    }

    result.normalize();

    return result;
  }

  Polynomial operator*(const NumT & n) const {
    Polynomial result;
    result.coefs.resize(coefs.size(), NumT());
    for (size_t i = 0; i < coefs.size(); i++) {
      result.coefs[i] = coefs[i] * n;
    }

    result.normalize();

    return result;
  }

  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial result;
    if (isZero() || rhs.isZero()) {
      return result;
    }
    result.coefs.assign(coefs.size() + rhs.coefs.size() - 1, NumT());

    for (size_t i = 0; i < coefs.size(); i++) {
      for (size_t j = 0; j < rhs.coefs.size(); j++) {
        result.coefs[i + j] = result.coefs[i + j] + (coefs[i] * rhs.coefs[j]);
      }
    }

    result.normalize();

    return result;
  }

  bool operator!=(const Polynomial & rhs) const { return !(*this == rhs); }

  bool operator==(const Polynomial & rhs) const { return coefs == rhs.coefs; }

  void addTerm(const NumT & c, unsigned p) {
    if (p >= coefs.size()) {
      coefs.resize(p + 1, NumT());
    }
    coefs[p] = coefs[p] + c;
    normalize();
  }

  Polynomial & operator+=(const Polynomial & rhs) {
    *this = *this + rhs;
    return *this;
  }

  Polynomial & operator-=(const Polynomial & rhs) {
    *this = *this - rhs;
    return *this;
  }

  Polynomial & operator*=(const Polynomial & rhs) {
    *this = *this * rhs;
    return *this;
  }

  Polynomial & operator*=(const NumT & n) {
    *this = *this * n;
    return *this;
  }

  template<typename T>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<T> & p);

  NumT eval(const NumT & x) const {
    NumT ans = NumT();
    for (size_t i = coefs.size(); i-- > 0;) {
      ans = ans * x + coefs[i];
    }

    return ans;
  }

  Polynomial derivative() const {
    Polynomial result;

    if (coefs.size() == 1) {
      result.coefs.assign(1, NumT());
      return result;
    }

    result.coefs.assign(coefs.size() - 1, NumT());
    
    for (size_t i = coefs.size(); i-- > 1;) {
      result.coefs[i - 1] = coefs[i] * static_cast<NumT>(i);
    }
    
    return result;
  }

  NumT operator()(const NumT & x) const {
    return eval(x);
  }
  
  template<typename T>
  friend class Polynomial;

  template<typename OtherNumT>
  Polynomial<OtherNumT> convert() const {
    Polynomial<OtherNumT> result;
    result.coefs.assign(coefs.size(), OtherNumT());
    for (size_t i = 0; i < coefs.size(); i++) {
      result.coefs[i] = OtherNumT(coefs[i]);
    }

    return result;
  }

  template<typename ToleranceT>
  NumT findZero(NumT x, unsigned maxSteps, const ToleranceT & tolerance, const ToleranceT & deriv_tolerance) {
    Polynomial derived = derivative();
    NumT xnew = x;
    for (unsigned i = 0; i <= maxSteps; i++) {
      NumT fx = eval(xnew);
      if (std::abs(fx) <= tolerance) {
        return xnew;
      }
      
      NumT dfx = derived.eval(xnew);
      if (std::abs(dfx) < deriv_tolerance) {
        throw convergence_failure<NumT>(xnew);
      }

      xnew = xnew - fx / dfx; 
    }
    throw convergence_failure<NumT>(xnew);
  }
};

template<typename NumT>
std::ostream & operator<<(std::ostream & os, const Polynomial<NumT> & p) {
  if (p.coefs.size() == 1 && p.coefs[0] == NumT()) {
    os << p.coefs[0];
    return os;
  }
  bool first = true;
  for (size_t i = p.coefs.size(); i-- > 0;) {
    const NumT & n = p.coefs[i];
    if (n == NumT()) {
      continue;
    }

    if (!first) {
      os << " + ";
    }

    first = false;
    os << n << "*x^" << i;
  }
  return os;
}

#endif
