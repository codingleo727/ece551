#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void sort_lines(std::vector<std::string> & lines) {
  std::sort(lines.begin(), lines.end());
  for (int i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << std::endl;
  }
}

int main(int argc, char * argv[]) {
  //WRITE YOUR CODE HERE!
  std::vector<std::string> lines;
  if (argc == 1) {
    std::string line;
    while(std::getline(std::cin, line)) {
      lines.push_back(line);
    }
  } 
  else {
    for (int i = 1; i < argc; i++) {
      std::string line;
      std::ifstream rfile(argv[i]);
      if (!rfile.is_open()) {
        std::perror("Failed to open file");
	exit(EXIT_FAILURE);
      }
      while (std::getline(rfile, line)) {
        lines.push_back(line);
      }
      rfile.close();
    }
  }
  sort_lines(lines);
  return EXIT_SUCCESS;
}
