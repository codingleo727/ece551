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

  // Initialize cat_arr
  catarray_t * cat_arr = malloc(sizeof(*cat_arr));
  cat_arr->arr = NULL;
  cat_arr->n = 0;

  char * line = NULL;
  size_t len = 0;

  while (getline(&line, &len, input) != -1) {
    line[strcspn(line, "\n")] = '\0';

    char * p = line;
    char * cat = NULL;
    char * last = p;
    while (*last != ':' && *last != '\0') {
      last++;
    }
    if (*last == '\0') {
      fprintf(stderr, "No colon detected\n");
      fclose(input);
      free(cat_arr->arr);
      free(cat_arr);
      free(line);
      exit(EXIT_FAILURE);
    }
    cat = strndup(p, last - p);  // Get category word first
    p = last + 1;

    char * word = NULL;
    char * word_last = p;
    while (*word_last != '\0') {
      word_last++;
    }
    word = strndup(p, word_last - p);  // Grab word

    int exists = 0;
    for (size_t i = 0; i < cat_arr->n; i++) {
      if (strcmp(cat_arr->arr[i].name, cat) == 0) {
        add_word(&cat_arr->arr[i], word);
        exists = 1;
      }
    }

    // Create a new category if it doesn't exist
    if (exists != 1) {
      cat_arr->arr = realloc(cat_arr->arr, (cat_arr->n + 1) * sizeof(*cat_arr->arr));

      // Initialize newly created category_t
      cat_arr->arr[cat_arr->n].name = strdup(cat);
      cat_arr->arr[cat_arr->n].words = NULL;
      cat_arr->arr[cat_arr->n].n_words = 0;

      add_word(&cat_arr->arr[cat_arr->n], word);
      cat_arr->n++;
    }
    free(cat);
    free(word);
  }

  printWords(cat_arr);
  for (size_t j = 0; j < cat_arr->n; j++) {
    for (size_t k = 0; k < cat_arr->arr[j].n_words; k++) {
      free(cat_arr->arr[j].words[k]);
    }
    free(cat_arr->arr[j].words);
    free(cat_arr->arr[j].name);
  }
  free(cat_arr->arr);
  free(cat_arr);
  free(line);

  if (fclose(input) != 0) {
    perror("Failed to close file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
