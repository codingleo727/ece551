#include <cstdlib>
#include <fstream>
#include <iostream>

#include "route.hpp"
#include "ship.hpp"
#include "util.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Please input 1 file only" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream input(argv[1]);
  std::string line;
  std::vector<Ship> fleet;
  std::vector<Route> routes;

  while (std::getline(input, line)) {
    try {
      parse_line(line, fleet, routes);
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

  return EXIT_SUCCESS;
}
