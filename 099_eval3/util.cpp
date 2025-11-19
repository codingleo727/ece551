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

/* Prints the route in the required format */
void print_route(std::vector<Route> & routes) {
  std::sort(routes.begin(), routes.end());
  for (std::vector<Route>::const_iterator it = routes.begin(); it != routes.end(); ++it) {
    std::cout << *it;
  }
}

/* Parses the line containing each ship's information into ships and routes */
void parse_fleet(const std::string & line,
                 std::vector<Ship *> & fleet,
                 std::vector<Route> & routes) {
  std::string name;
  std::vector<std::string> info;
  std::string source;
  std::string dest;
  unsigned capacity = 0;
  std::vector<Cargo> cargos_carried;

  std::vector<std::string> ship_info;
  parse_fleet_info(line, ship_info, name, info, source, dest, capacity);

  parse_ship(fleet, name, info, source, dest, capacity, cargos_carried);
  parse_route(routes, source, dest, capacity);
}

/* Parses the line for the ship's info (name, type info, source, destination, and capacity) */
void parse_fleet_info(const std::string & line,
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

/* Adds a ship to the fleet */
void parse_ship(std::vector<Ship *> & fleet,
                std::string & name,
                std::vector<std::string> & info,
                std::string & source,
                std::string & dest,
                unsigned total_capacity,
                std::vector<Cargo> & cargos_carried) {
  Ship * member;
  std::string ship_type = info[0];
  std::vector<std::string> capabilities;
  if (ship_type == "Container") {
    unsigned num_slots = to_unsigned(info[1]);
    for (size_t i = 2; i < info.size(); i++) {
      capabilities.push_back(info[i]);
    }
    member = new Container(name,
                           ship_type,
                           source,
                           dest,
                           total_capacity,
                           0,
                           capabilities,
                           cargos_carried,
                           num_slots);
  }
  /* else if (info[0] == "Tanker") {
  }
  else if (info[0] == "Animal") {
  }*/

  for (std::vector<Ship *>::iterator it = fleet.begin(); it != fleet.end(); ++it) {
    if ((*it)->get_name() == name) {
      throw duplicate_name();  // In case of duplicate ship names
    }
  }
  fleet.push_back(member);
}

/* Adds a route */
void parse_route(std::vector<Route> & routes,
                 std::string & source,
                 std::string & dest,
                 unsigned capacity) {
  Route route(source, dest, capacity);
  std::vector<Route>::iterator found_route =
      std::find(routes.begin(), routes.end(), route);
  if (found_route != routes.end()) {
    found_route->update_capacity(
        capacity);  // If same route, updates the capacity of said route
  }
  else {
    routes.push_back(route);
  }
}

/* Frees the memory within fleet */
void clear_fleet(std::vector<Ship *> fleet) {
  for (size_t i = 0; i < fleet.size(); ++i) {
    delete fleet[i];
  }
  fleet.clear();
}

void parse_cargo(const std::string & line, std::vector<Cargo> & cargos) {
  std::vector<std::string> cargo_info;
  std::string name;
  std::string source;
  std::string dest;
  unsigned capacity = 0;
  std::vector<std::string> properties;

  cargo_info = split(line, ',');
  name = cargo_info[0];
  source = cargo_info[1];
  dest = cargo_info[2];
  capacity = to_unsigned(cargo_info[3]);
  for (size_t i = 4; i < cargo_info.size(); ++i) {
    std::string word_to_remove = "hazardous-";
    size_t pos = cargo_info[i].find(word_to_remove);
    if (pos != std::string::npos) {
      cargo_info[i].erase(pos, word_to_remove.length());
    }
    properties.push_back(cargo_info[i]);
  }
  Cargo cargo(name, source, dest, capacity, properties);
  cargos.push_back(cargo);
}
