#ifndef UTIL_HPP
#define UTIL_HPP

#include <exception>
#include <string>
#include <vector>

#include "route.hpp"
#include "ship.hpp"

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
unsigned to_unsigned(const std::string & s);
void print_route(std::vector<Route> & routes);
void parse_line(const std::string & line,
                std::vector<Ship> & fleet,
                std::vector<Route> & routes);
void parse_info(const std::string & line,
                std::vector<std::string> & ship_info,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned & capacity);
void parse_ship(std::vector<Ship> & fleet,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned capacity);
void parse_route(std::vector<Route> & routes,
                 std::string & source,
                 std::string & dest,
                 unsigned capacity);

#endif
