#include "rand_story.h"

/* Parses the blank line in the story file to get the category */
char * parse_blank_line(char ** p) {
  (**p)++;  // Skip first underscore
  char * start = *p;
  while (**p != '_' && **p != '\0') {
    (*p)++;
  }
  if (**p == '\0') {
    fprintf(stderr, "\nNo matching underscore for this blank encounter!\n");
    exit(EXIT_FAILURE);
  }
  size_t len = *p - start;
  (*p)++;  // Move past second underscore
  return strndup(start, len);
}

/* Adds the word into the word list */
void add_word(category_t * category, const char * word) {
  category->words =
      realloc(category->words, (category->n_words + 1) * sizeof(*category->words));
  category->words[category->n_words] = strdup(word);
  category->n_words++;
}

/* Parses the line to grab the category name and the word */
int parse_category_line(char * line, char ** cat_name, char ** word) {
  char * p = line;
  char * last = p;
  // Grabs category first
  while (*last != ':' && *last != '\0') {
    last++;
  }
  // Case when there is no colon in the line
  if (*last == '\0') {
    return 0;
  }
  *cat_name = strndup(p, last - p);
  p = last + 1;

  char * word_last = p;
  // Grabs word second
  while (*word_last != '\0') {
    word_last++;
  }
  *word = strndup(p, word_last - p);
  return 1;
}

/* Checks if category exists */
int check_category_exists(catarray_t * cat_arr, char ** cat_name) {
  for (size_t i = 0; i < cat_arr->n; i++) {
    if (strcmp(cat_arr->arr[i].name, *cat_name) == 0) {
      return i;  // Returns the index of the category if found
    }
  }
  return -1;  // Returns -1 if category is not found
}

/* Creates a new category and adds the word into the category */
void create_new_category(catarray_t * cat_arr, char ** cat_name, char ** word) {
  cat_arr->arr = realloc(cat_arr->arr, (cat_arr->n + 1) * sizeof(*cat_arr->arr));

  // Initialize newly created category_t
  cat_arr->arr[cat_arr->n].name = strdup(*cat_name);
  cat_arr->arr[cat_arr->n].words = NULL;
  cat_arr->arr[cat_arr->n].n_words = 0;

  add_word(&cat_arr->arr[cat_arr->n], *word);
  cat_arr->n++;
}

/* Free the catarray */
void free_catarr(catarray_t * cat_arr) {
  for (size_t j = 0; j < cat_arr->n; j++) {
    for (size_t k = 0; k < cat_arr->arr[j].n_words; k++) {
      free(cat_arr->arr[j].words[k]);
    }
    free(cat_arr->arr[j].words);
    free(cat_arr->arr[j].name);
  }
  free(cat_arr->arr);
  free(cat_arr);
}
