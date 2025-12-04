#include <cstdlib>
#include <fstream>
#include <iostream>

#include "parsing_util.hpp"
#include "route.hpp"
#include "ships.hpp"
#include "util.hpp"

int main(int argc, char * argv[]) {
  try {
    if (argc != 2) {
      throw invalid_argument_format(1);
    }
    run(argv[1], NULL, 1, 0);
  }
  catch (const invalid_argument_format & e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
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

  return EXIT_SUCCESS;
}
