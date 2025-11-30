#ifndef PARSING_UTIL_HPP
#define PARSING_UTIL_HPP

#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "route.hpp"
#include "ships.hpp"
#include "util.hpp"

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
void loading_process(std::vector<Ship *> & fleet, std::vector<Cargo> & cargos);
void loading_cargo_begin(std::vector<Ship *> & fleet, std::vector<Cargo> & cargos);
void loading_cargo_process(int num_ships,
                           std::vector<Ship *> & available_ships,
                           const Cargo & cargo);
void loading_cargo_finish(const std::vector<Ship *> & fleet);

#endif
