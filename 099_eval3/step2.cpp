#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "cargo.hpp"
#include "parsing_util.hpp"
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

  loading_process(fleet, cargos);

  return EXIT_SUCCESS;
}
