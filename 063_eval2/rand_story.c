#include "rand_story.h"

void add_word(category_t * arr, const char * word) {
  arr->words = realloc(arr->words, (arr->n_words + 1) * sizeof(*arr->words));
  arr->words[arr->n_words] = strdup(word);
  arr->n_words++;
}
