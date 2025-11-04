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
    virtual long evaluate() const = 0;
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
    virtual long evaluate() const {
      return num;
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
    virtual std::string toString() const {
      std::stringstream ss;
      ss << "(" << e1->toString() << " + " << e2->toString() << ")";
      return ss.str();
    }
    virtual long evaluate() const {
      return e1->evaluate() + e2->evaluate();
    }
    virtual ~PlusExpression() {
      delete e1;
      delete e2;
    }
};

class MinusExpression : public Expression {
  private:
    Expression * e1;
    Expression * e2;
  public:
    MinusExpression(Expression * lhs, Expression * rhs): e1(lhs), e2(rhs) {
    }
    virtual std::string toString() const {
      std::stringstream ss;
      ss << "(" << e1->toString() << " - " << e2->toString() << ")";
      return ss.str();
    }
    virtual long evaluate() const {
      return e1->evaluate() - e2->evaluate();
    }
    virtual ~MinusExpression() {
      delete e1;
      delete e2;
    }
};

class TimesExpression : public Expression {
  private:
    Expression * e1;
    Expression * e2;
  public:
    TimesExpression(Expression * lhs, Expression * rhs): e1(lhs), e2(rhs) {
    }
    virtual std::string toString() const {
      std::stringstream ss;
      ss << "(" << e1->toString() << " * " << e2->toString() << ")";
      return ss.str();
    }
    virtual long evaluate() const {
      return e1->evaluate() * e2->evaluate();
    }
    virtual ~TimesExpression() {
      delete e1;
      delete e2;
    }
};

class DivExpression : public Expression {
  private:
    Expression * e1;
    Expression * e2;
  public:
    DivExpression(Expression * lhs, Expression * rhs): e1(lhs), e2(rhs) {
    }
    virtual std::string toString() const {
      std::stringstream ss;
      ss << "(" << e1->toString() << " / " << e2->toString() << ")";
      return ss.str();
    }
    virtual long evaluate() const {
      return e1->evaluate() / e2->evaluate();
    }
    virtual ~DivExpression() {
      delete e1;
      delete e2;
    }
};

#endif
