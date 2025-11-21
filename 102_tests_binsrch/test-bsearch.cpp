#include <cmath>
#include <iostream>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

class PositiveFunction : public Function<int, int> {
public: 
  virtual int invoke(int arg) {
    return 2;
  }
};

class NegativeFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return -2;
  }
};

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 5000000 * (sin(arg / 200000.0) - 0.3);
  }
};

class PositiveSlopeFunction : public Function<int, int> {
public:  
  virtual int invoke(int arg) {
    return 2 * arg + 2;
  }
};

class NegativeSlopeFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return -arg;
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int num;
  if (high > low) {
    num = log(high - low) / log(2) + 1;
  }
  else {
    num = 1;
  }
  CountedIntFn * function = new CountedIntFn(num, f, mesg);
  int ans = binarySearchForZero(function, low, high);
  if (ans != expected_ans) {
    std::cerr << "Result of function " << mesg << " is wrong!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main() {
  PositiveFunction pf;
  NegativeFunction nf;
  SinFunction sf;
  PositiveSlopeFunction psf;
  NegativeSlopeFunction nsf;

  check(&pf, -100, 100, -100, "Positive in range [-100, 100]");
  check(&pf, 100, 1000, 100, "Positive in range [10, 1000]");
  check(&pf, -1000, -100, -1000, "Positive in range [-1000, -100]");
  check(&pf, 0, 0, 0, "Positive in the range [0,0]");

  check(&nf, -100, 100, 99, "Negative in range [-100, 100]");
  check(&nf, 10, 1000, 999, "Negative in range [10, 1000]");
  check(&nf, -100, -10, -11, "Negative in range [-100, -10]");
  check(&nf, 0, 0, 0, "Negative in the range [0,0]");
 
  check(&sf, 0, 150000, 60938, "Sin in range [0, 150000]");

  check(&psf, -100, 100, -1, "Positive slope function in range [-100, 100]");
  check(&psf, 10, 1000, 10, "Positive slope function in range [10, 1000]");
  check(&psf, -100, -10, -11, "Positive slope function in range [-100, -10]");
  check(&psf, 0, 0, 0, "Positive slope function in range [0, 0]");

  check(&nsf, -100, 100, 0, "Negative slope function in range [-100, 100]");
  check(&nsf, 10, 1000, 999, "Negative slope function in range [10, 1000]");
  check(&nsf, -100, -10, -100, "Negative slope function in range [-100, -10]");
  check(&nsf, 0, 0, 0, "Negative slope function in range [0, 0]");
}
