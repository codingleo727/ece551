#ifndef PARSING_UTIL_HPP
#define PARSING_UTIL_HPP

#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "avlmultimap03.hpp"
#include "cargo.hpp"
#include "route.hpp"
#include "ships.hpp"
#include "util.hpp"

void run(char * file1, char * file2, int option);
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
void sort_cargo(std::vector<Cargo> & cargos);
AVLMultiMap<unsigned, Ship *> build_ship_tree(const std::vector<Ship *> & fleet);
void loading_cargo_tree(AVLMultiMap<unsigned, Ship *> & ship_tree, const Cargo & cargo);
void loading_process(std::vector<Ship *> & fleet,
                     std::vector<Cargo> & cargos,
                     int option);
void loading_cargo_begin(std::vector<Ship *> & fleet,
                         std::vector<Cargo> & cargos,
                         int option);
void loading_cargo_process(int num_ships,
                           std::vector<Ship *> & available_ships,
                           const Cargo & cargo);
void loading_cargo_process_tree(const Ship * ship,
                                const Cargo & cargo,
                                unsigned remaining_capacity);
void loading_cargo_finish(const std::vector<Ship *> & fleet);
#endif
