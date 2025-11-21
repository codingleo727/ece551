#ifndef UTIL_HPP
#define UTIL_HPP

#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "route.hpp"
#include "ships.hpp"

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
unsigned to_unsigned(const std::string & num);
signed to_signed(const std::string & num);
void print_route(std::vector<Route> & routes);
void parse_fleet(const std::string & line,
                 std::vector<Ship *> & fleet,
                 std::vector<Route> & routes);
void parse_fleet_info(const std::string & line,
                      std::vector<std::string> & ship_info,
                      std::string & name,
                      std::vector<std::string> & info,
                      std::string & source,
                      std::string & dest,
                      unsigned & capacity);
void parse_ship(std::vector<Ship *> & fleet,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned total_capacity,
                std::vector<Cargo> & cargos_carried);
void parse_route(std::vector<Route> & routes,
                 std::string & source,
                 std::string & dest,
                 unsigned capacity);
void clear_fleet(std::vector<Ship *> fleet);
void parse_cargo(const std::string & line, std::vector<Cargo> & cargos);

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
