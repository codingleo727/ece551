#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "cargo.hpp"
#include "route.hpp"
#include "ships.hpp"
#include "util.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "Please input in the format: ./ships-step2 \"ship file\" \"cargo file\""
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream fleet_file(argv[1]);
  std::ifstream cargo_file(argv[2]);
  std::string line;
  std::vector<Ship *> fleet;
  std::vector<Route> routes;
  std::vector<Cargo> cargos;

  while (std::getline(fleet_file, line)) {
    try {
      parse_fleet(line, fleet, routes);
    }
    catch (const parsing_failure & e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    catch (const duplicate_name & e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    catch (...) {
      std::cerr << "An unknown error occurred" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  while (std::getline(cargo_file, line)) {
    parse_cargo(line, cargos);
  }

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
    if (num_ships > 0) {
      std::cout << num_ships << " ships can carry the " << (*c).get_name() << " from "
                << (*c).get_source() << " to " << (*c).get_dest() << "\n";
      for (std::vector<Ship *>::iterator as = available_ships.begin();
           as != available_ships.end();
           ++as) {
        std::cout << "  " << (*as)->get_name() << "\n";
      }
      Ship * first_ship = available_ships[0];
      std::cout << "  **Loading the cargo onto " << (*first_ship).get_name() << "**"
                << "\n";

      (*first_ship).load_cargo((*c));
    }
    else {
      std::cout << "No ships can carry the " << (*c).get_name() << " from "
                << (*c).get_source() << " to " << (*c).get_dest() << "\n";
    }
  }
  std::cout << "---Done Loading---Here are the ships---\n";
  for (std::vector<Ship *>::iterator s = fleet.begin(); s != fleet.end(); ++s) {
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

  clear_fleet(fleet);

  return EXIT_SUCCESS;
}
