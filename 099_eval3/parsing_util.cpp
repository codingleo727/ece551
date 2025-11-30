#include "parsing_util.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "util.hpp"

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
  capacity = to_number<unsigned>(ship_info[4]);
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
    unsigned num_slots = 0;
    if (info.size() > 1) {
      num_slots = to_number<unsigned>(info[1]);
      for (size_t i = 2; i < info.size(); ++i) {
        capabilities.push_back(info[i]);
      }
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
  else if (info[0] == "Tanker") {
    signed min_temp = to_number<signed>(info[1]);
    signed max_temp = to_number<signed>(info[2]);
    unsigned num_tanks = to_number<unsigned>(info[3]);
    for (size_t i = 4; i < info.size(); ++i) {
      capabilities.push_back(info[i]);
    }
    member = new Tanker(name,
                        ship_type,
                        source,
                        dest,
                        total_capacity,
                        0,
                        capabilities,
                        cargos_carried,
                        min_temp,
                        max_temp,
                        num_tanks);
  }
  else if (info[0] == "Animals") {
    unsigned size = to_number<unsigned>(info[1]);
    member = new Animal(name,
                        ship_type,
                        source,
                        dest,
                        total_capacity,
                        0,
                        capabilities,
                        cargos_carried,
                        size);
  }
  else {
    throw parsing_failure();
  }

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

/* Adds a cargo */
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
  capacity = to_number<unsigned>(cargo_info[3]);
  for (size_t i = 4; i < cargo_info.size(); ++i) {
    properties.push_back(cargo_info[i]);
  }
  Cargo cargo(name, source, dest, capacity, properties);
  cargos.push_back(cargo);
}

/* Simulates the loading process of cargos onto the fleet */
void loading_process(std::vector<Ship *> & fleet, std::vector<Cargo> & cargos) {
  loading_cargo_begin(fleet, cargos);
  loading_cargo_finish(fleet);
  clear_fleet(fleet);
}

/* Begins the cargo loading process */
void loading_cargo_begin(std::vector<Ship *> & fleet, std::vector<Cargo> & cargos) {
  for (std::vector<Cargo>::iterator c = cargos.begin(); c != cargos.end(); ++c) {
    int num_ships = 0;
    std::vector<Ship *> available_ships;
    for (std::vector<Ship *>::iterator s = fleet.begin(); s != fleet.end(); ++s) {
      if ((*s)->can_load(*c)) {
        num_ships++;
        available_ships.push_back(*s);
      }
    }
    std::sort(available_ships.begin(), available_ships.end(), ship_ptr_less);
    loading_cargo_process(num_ships, available_ships, *c);
  }
}

/* Loads the cargo onto the available ship */
void loading_cargo_process(int num_ships,
                           std::vector<Ship *> & available_ships,
                           const Cargo & cargo) {
  if (num_ships > 0) {
    std::cout << num_ships << " ships can carry the " << cargo.get_name() << " from "
              << cargo.get_source() << " to " << cargo.get_dest() << "\n";
    for (std::vector<Ship *>::iterator as = available_ships.begin();
         as != available_ships.end();
         ++as) {
      std::cout << "  " << (*as)->get_name() << "\n";
    }
    Ship * first_ship = available_ships[0];
    std::cout << "  **Loading the cargo onto " << (*first_ship).get_name() << "**"
              << "\n";

    (*first_ship).load_cargo(cargo);
  }
  else {
    std::cout << "No ships can carry the " << cargo.get_name() << " from "
              << cargo.get_source() << " to " << cargo.get_dest() << "\n";
  }
}

/* Finishes loading all the loadable cargos onto the fleet */
void loading_cargo_finish(const std::vector<Ship *> & fleet) {
  std::cout << "---Done Loading---Here are the ships---\n";
  for (std::vector<Ship *>::const_iterator s = fleet.begin(); s != fleet.end(); ++s) {
    std::cout << "The " << (*s)->get_ship_type() << " Ship " << (*s)->get_name() << "("
              << (*s)->get_used_capacity() << "/" << (*s)->get_total_capacity()
              << ") is carrying : \n";
    std::vector<Cargo> cargos_carried = (*s)->get_cargos_carried();
    for (std::vector<Cargo>::iterator c = cargos_carried.begin();
         c != cargos_carried.end();
         ++c) {
      std::cout << "  " << (*c).get_name() << "(" << (*c).get_capacity() << ")\n";
    }
    (*s)->print_remaining_space();
  }
}
