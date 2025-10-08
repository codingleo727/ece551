#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort_lines(void * file) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t len;
  size_t i = 0;
  while (getline(&curr, &len, file) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sort_lines(stdin);
  }
  if (argc > 1) {
    for (int i = 0; i < argc - 1; i++) {
      FILE * input = fopen(argv[i + 1], "r");
      if (input == NULL) {
        perror("Empty file");
	exit(EXIT_FAILURE);
      }
      sort_lines(input);
      if (fclose(input) != 0) {
      	perror("Failed to close file");
	exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
