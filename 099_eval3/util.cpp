#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

std::vector<std::string> split(const std::string & line, const char delim) {
  std::vector<std::string> str_vector;
  std::string word;
  for (std::string::const_iterator it = line.begin(); it != line.end(); ++it) {
    char c = *it;
    if (c == delim) {
      if (word.empty()) {
        throw parsing_failure();
      }
      str_vector.push_back(word);
      word.clear();
    }
    else {
      word.push_back(c);
    }
  }

  if (word.empty()) {
    throw parsing_failure();
  }
  str_vector.push_back(word);

  return str_vector;
}

unsigned to_unsigned(const std::string & num) {
  std::stringstream ss(num);
  unsigned value;
  ss >> value;
  return value;
}

void print_route(std::vector<Route> & routes) {
  std::sort(routes.begin(), routes.end());
  for (std::vector<Route>::const_iterator it = routes.begin(); it != routes.end(); ++it) {
    std::cout << *it;
  }
}

void parse_line(const std::string & line,
                std::vector<Ship> & fleet,
                std::vector<Route> & routes) {
  std::string name;
  std::vector<std::string> info;
  std::string source;
  std::string dest;
  unsigned capacity = 0;

  std::vector<std::string> ship_info;
  parse_info(line, ship_info, name, info, source, dest, capacity);

  parse_ship(fleet, name, info, source, dest, capacity);
  parse_route(routes, source, dest, capacity);
}

void parse_info(const std::string & line,
                std::vector<std::string> & ship_info,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned & capacity) {
  ship_info = split(line, ':');
  if (ship_info.size() != 5) {
    throw parsing_failure();
  }
  name = ship_info[0];
  info = split(ship_info[1], ',');
  source = ship_info[2];
  dest = ship_info[3];
  capacity = to_unsigned(ship_info[4]);
}

void parse_ship(std::vector<Ship> & fleet,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned capacity) {
  Ship member(name, info, source, dest, capacity);
  for (std::vector<Ship>::iterator it = fleet.begin(); it != fleet.end(); ++it) {
    if (it->get_name() == name) {
      throw duplicate_name();
    }
  }
  fleet.push_back(member);
}

void parse_route(std::vector<Route> & routes,
                 std::string & source,
                 std::string & dest,
                 unsigned capacity) {
  Route route(source, dest, capacity);
  std::vector<Route>::iterator found_route =
      std::find(routes.begin(), routes.end(), route);
  if (found_route != routes.end()) {
    found_route->update_capacity(capacity);
  }
  else {
    routes.push_back(route);
  }
}
