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
  try {
    if (argc != 3) {
      throw invalid_argument_format();
    }
    run(argv[1], argv[2]);
  }
  catch (const invalid_argument_format & e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  catch (const failed_to_open_file & e) {
    std::cerr << "Error: " << e.what() << std::endl;
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
