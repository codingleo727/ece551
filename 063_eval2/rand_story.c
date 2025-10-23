#include "rand_story.h"

void add_word(category_t * arr, const char * word) {
  arr->words = realloc(arr->words, (arr->n_words + 1) * sizeof(*arr->words));
  arr->words[arr->n_words] = strdup(word);
  arr->n_words++;
}

int parse_category_line(char * line, char ** category, char ** word) {
  char * p = line;
  char * last = p;
  while (*last != ':' && *last != '\0') {
    last++;
  }
  if (*last == '\0') {
    return 0;
  }
  *category = strndup(p, last - p);
  p = last + 1;

  char * word_last = p;
  while (*word_last != '\0') {
    word_last++;
  }
  *word = strndup(p, word_last - p);
  return 1;
}
