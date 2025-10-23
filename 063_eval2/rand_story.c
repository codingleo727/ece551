#include "rand_story.h"

/* Adds the word into the word list */
void add_word(category_t * arr, const char * word) {
  arr->words = realloc(arr->words, (arr->n_words + 1) * sizeof(*arr->words));
  arr->words[arr->n_words] = strdup(word);
  arr->n_words++;
}

/* Parses the line to grab the category and the word */
int parse_category_line(char * line, char ** category, char ** word) {
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
  *category = strndup(p, last - p);
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
int check_category_exists(catarray_t * cat_arr, char ** category) {
  for (size_t i = 0; i < cat_arr->n; i++) {
    if (strcmp(cat_arr->arr[i].name, *category) == 0) {
      return i;  // Returns the index of the category if found
    }
  }
  return -1;  // Returns -1 if category is not found
}

/* Creates a new category and adds the word into the category */
void create_new_category(catarray_t * cat_arr, char ** category, char ** word) {
  cat_arr->arr = realloc(cat_arr->arr, (cat_arr->n + 1) * sizeof(*cat_arr->arr));

  // Initialize newly created category_t
  cat_arr->arr[cat_arr->n].name = strdup(*category);
  cat_arr->arr[cat_arr->n].words = NULL;
  cat_arr->arr[cat_arr->n].n_words = 0;

  add_word(&cat_arr->arr[cat_arr->n], *word);
  cat_arr->n++;
}
