#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

/* Splits a string according to the delim */
std::vector<std::string> split(const std::string & line, const char delim) {
  std::vector<std::string> str_vector;
  std::string word;
  for (std::string::const_iterator it = line.begin(); it != line.end(); ++it) {
    char c = *it;
    if (c == delim) {
      if (word.empty()) {
        throw parsing_failure();  // In case of invalid format
      }
      str_vector.push_back(word);
      word.clear();
    }
    else {
      word.push_back(c);
    }
  }

  if (word.empty()) {
    throw parsing_failure();  // In case of invalid format
  }
  str_vector.push_back(word);

  return str_vector;
}

/* Converts a string to an unsigned integer */
unsigned to_unsigned(const std::string & num) {
  std::stringstream ss(num);
  unsigned value;
  ss >> value;

  if (ss.fail()) {
    throw parsing_failure();  // In case if string is not a valid integer
  }

  char leftover;
  if (ss >> leftover) {
    throw parsing_failure();  // In case if string is not a valid integer
  }

  return value;
}

/* Converts a string to a signed integer */
signed to_signed(const std::string & num) {
  std::stringstream ss(num);
  signed value;
  ss >> value;

  if (ss.fail()) {
    throw parsing_failure();
  }

  char leftover;
  if (ss >> leftover) {
    throw parsing_failure();
  }

  return value;
}
