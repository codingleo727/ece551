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
    // parse_cargo(line, cargos); To be implemented
    std::vector<std::string> cargo_info;
    cargo_info = split(line, ',');
    std::string name;
    std::string source;
    std::string dest;
    unsigned num_slots = 0;
    std::vector<std::string> properties;
    name = cargo_info[0];
    source = cargo_info[1];
    dest = cargo_info[2];
    num_slots = to_unsigned(cargo_info[3]);
    for (size_t i = 4; i < cargo_info.size(); ++i) {
      properties.push_back(cargo_info[i]);
    }
  }

  print_route(routes);
  clear_fleet(fleet);

  return EXIT_SUCCESS;
}
