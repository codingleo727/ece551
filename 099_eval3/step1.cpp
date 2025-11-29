#include <cstdlib>
#include <fstream>
#include <iostream>

#include "parsing_util.hpp"
#include "route.hpp"
#include "ships.hpp"
#include "util.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Please input in the format: ./ships-step1 \"input filename\""
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream input(argv[1]);
  std::string line;
  std::vector<Ship *> fleet;
  std::vector<Route> routes;

  while (std::getline(input, line)) {
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

  print_route(routes);
  clear_fleet(fleet);

  return EXIT_SUCCESS;
}
