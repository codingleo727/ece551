#include <stdio.h>

#include "provided.h"
#include "string.h"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Please input a file\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t len = 0;

  while (getline(&line, &len, f) != -1) {
    line[strcspn(line, "\n")] = '\0';

    char * p = line;

    while (*p != '\0') {
      if (*p != '_') {
        printf("%c", *p);
        p++;
      }
      else {
        char * first = p + 1;
        char * last = first;
        while (*last != '_') {
          if (*last == '\0') {
            printf("\n");
            fprintf(stderr, "No matching underscore for this blank encounter!\n");
            exit(EXIT_FAILURE);
          }
          last++;
        }
        char * cat = strndup(first, last - first);
        if (strlen(cat) == 0) {
          printf("\n");
          fprintf(stderr, "No category written at this blank encounter!\n");
          exit(EXIT_FAILURE);
        }
        const char * word = chooseWord(cat, NULL);
        printf("%s", word);
        free(cat);
        p = last + 1;
      }
    }
    printf("\n");
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
