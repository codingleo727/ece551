#ifndef UTIL_HPP
#define UTIL_HPP

#include <exception>
#include <sstream>
#include <string>
#include <vector>

class parsing_failure : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "File content does not have the correct format";
  }
};

class duplicate_name : public std::exception {
 public:
  virtual const char * what() const throw() { return "Duplicate ship names detected"; }
};

std::vector<std::string> split(const std::string & line, const char delim);

/* Converts a number string to a number in the target type */
template<typename T>
T to_number(const std::string & num) {
  std::stringstream ss(num);
  long value;
  ss >> value;

  if (ss.fail()) {
    throw parsing_failure();
  }

  char leftover;
  if (ss >> leftover) {
    throw parsing_failure();
  }

  if (value < 0 && static_cast<T>(-1) > 0) {
    throw parsing_failure();
  }

  return static_cast<T>(value);
}
#endif
