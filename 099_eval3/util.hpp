#ifndef UTIL_HPP
#define UTIL_HPP

#include <exception>
#include <sstream>
#include <string>
#include <vector>

class invalid_argument_format : public std::exception {
 private:
  int step;

 public:
  invalid_argument_format(int step_) : step(step_) {}
  virtual const char * what() const throw() {
    if (step == 1) {
      return "Please input in the format: ./ships-step1 \"ship file\"";
    }
    else {
      return "Please input in the format: ./ships-step# \"ship file\" \"cargo file\"";
    }
  }
};

class failed_to_open_file : public std::exception {
 private:
  int step;

 public:
  failed_to_open_file(int step_) : step(step_) {}
  virtual const char * what() const throw() {
    if (step == 1) {
      return "File does not exist or failed to open file";
    }
    else {
      return "One or both files do not exist or failed to open";
    }
  }
};

class parsing_failure : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "One or both input files do not have the correct format";
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
    throw parsing_failure();  // In case if the string is not a number
  }

  char leftover;
  if (ss >> leftover) {
    throw parsing_failure();  // In case of a string being after the number
  }

  if (value < 0 && static_cast<T>(-1) > 0) {
    throw parsing_failure();  // In case of negative numbers for unsigned
  }

  return static_cast<T>(value);
}
#endif
