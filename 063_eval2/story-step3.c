#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Please input a word file and a story file\n");
    exit(EXIT_FAILURE);
  }

  FILE * w_file = fopen(argv[1], "r");
  if (w_file == NULL) {
    perror("Failed to open word file");
    exit(EXIT_FAILURE);
  }

  FILE * s_file = fopen(argv[2], "r");
  if (s_file == NULL) {
    perror("Failed to open story file");
    exit(EXIT_FAILURE);
  }

  catarray_t * cat_arr = parse_word_file(w_file);
  parse_story_file(s_file, cat_arr);

  free_catarr(cat_arr);

  if (fclose(w_file) != 0) {
    perror("Failed to close word file");
    exit(EXIT_FAILURE);
  }

  if (fclose(s_file) != 0) {
    perror("Failed to close story file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
