#include <iostream>

#include "route.hpp"
#include "ship.hpp"
#include "util.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "Please input 2 files only" << std::endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
