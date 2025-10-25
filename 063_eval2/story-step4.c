#include "rand_story.h"

int main(int argc, char * argv[]) {
  FILE * w_file = NULL;
  FILE * s_file = NULL;
  int option = 0;

  if (argc == 3) {
    w_file = fopen(argv[1], "r");
    if (w_file == NULL) {
      perror("Failed to open word file");
      exit(EXIT_FAILURE);
    }

    s_file = fopen(argv[2], "r");
    if (s_file == NULL) {
      perror("Failed to open story file");
      exit(EXIT_FAILURE);
    }
  }
  else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    w_file = fopen(argv[2], "r");
    if (w_file == NULL) {
      perror("Failed to open word file");
      exit(EXIT_FAILURE);
    }

    s_file = fopen(argv[3], "r");
    if (s_file == NULL) {
      perror("Failed to open story file");
      exit(EXIT_FAILURE);
    }
    option = 1;
  }
  else {
    fprintf(stderr,
            "Invalid number of inputs. Please input in the format (-n (optional), "
            "word_file, story_file\n");
    exit(EXIT_FAILURE);
  }

  catarray_t * cat_arr = parse_word_file(w_file);
  parse_story_file(s_file, cat_arr, option);

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
