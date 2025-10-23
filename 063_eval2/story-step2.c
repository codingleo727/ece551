#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Please input one file only \n");
    exit(EXIT_FAILURE);
  }

  FILE * input = fopen(argv[1], "r");

  if (input == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

  /*
  // Initialize cat_arr
  catarray_t * cat_arr = malloc(sizeof(*cat_arr));
  cat_arr->arr = NULL;
  cat_arr->n = 0;

  char * line = NULL;
  size_t len = 0;
  char * cat = NULL;
  char * word = NULL;

  while (getline(&line, &len, input) != -1) {
    line[strcspn(line, "\n")] = '\0';

    // cat and word is parsed within parse_category_line
    if (parse_category_line(line, &cat, &word) == 0) {
      fprintf(stderr, "No colon detected\n");
      exit(EXIT_FAILURE);
    }

    int cat_index = check_category_exists(cat_arr, &cat);
    if (cat_index != -1) {
      add_word(&cat_arr->arr[cat_index], word);
    }
    else {
      create_new_category(cat_arr, &cat, &word);
    }

    free(cat);
    free(word);
  }

  printWords(cat_arr);

  free(line);
  free_catarr(cat_arr);
  */
  catarray_t * cat_arr = parse_word_file(input);
  free_catarr(cat_arr);
  if (fclose(input) != 0) {
    perror("Failed to close file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
