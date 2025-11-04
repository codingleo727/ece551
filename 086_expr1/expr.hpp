#ifndef EXPR_HPP
#define EXPR_HPP

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <sstream>
#include <iostream>

class Expression {
  public:
    virtual std::string toString() const = 0;
    virtual ~Expression() {}
};

class NumExpression : public Expression {
  private:
    long num;
  public:
    NumExpression(long n): num(n) {
    }
    virtual std::string toString() const {
      std::stringstream ss;
      ss << num;
      return ss.str();
    }
    virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  private:
    Expression * e1;
    Expression * e2;
  public:
    PlusExpression(Expression * lhs, Expression * rhs): e1(lhs), e2(rhs) {
    }
    std::string toString() const {
      std::stringstream ss;
      ss << "(" << e1->toString() << " + " << e2->toString() << ")";
      return ss.str();
    }
    virtual ~PlusExpression() {
      delete e1;
      delete e2;
    }
};

#endif
