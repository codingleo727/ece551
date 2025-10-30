#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void sort_lines(std::vector<std::string> & lines) {
  std::sort(lines.begin(), lines.end());
  for (int i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << "\n";
  }
}

int main(int argc, char * argv[]) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(std::cin, line)) {
      lines.push_back(line);
    }
    sort_lines(lines);
  } 
  else {
    for (int i = 1; i < argc; i++) {
      std::vector<std::string> lines;
      std::string line;
      std::ifstream rfile(argv[i]);
      if (!rfile.is_open()) {
        std::perror("Failed to open file");
	exit(EXIT_FAILURE);
      }
      while (std::getline(rfile, line)) {
        lines.push_back(line);
      }
      sort_lines(lines);
    }
  }
  return EXIT_SUCCESS;
}
