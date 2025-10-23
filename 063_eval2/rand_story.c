#include "rand_story.h"

/* If file is a story file, prints out the story */
void parse_story_file(FILE * s_file) {
  char * line = NULL;
  size_t len = 0;

  while (getline(&line, &len, s_file) != -1) {
    line[strcspn(line, "\n")] = '\0';

    char * p = line;

    // Prints out the character if not a blank encounter
    // If it's a blank encounter, grab the category word at print out "cat"
    while (*p != '\0') {
      if (*p != '_') {
        printf("%c", *p);
        p++;
      }
      else {
        char * cat = parse_blank_line(&p);
        const char * word = chooseWord(cat, NULL);
        printf("%s", word);
        free(cat);
      }
    }
    printf("\n");
  }

  free(line);
}

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

catarray_t * parse_word_file(FILE * w_file) {
  // Initialize cat_arr
  catarray_t * cat_arr = malloc(sizeof(*cat_arr));
  cat_arr->arr = NULL;
  cat_arr->n = 0;

  char * line = NULL;
  size_t len = 0;
  char * cat = NULL;
  char * word = NULL;

  while (getline(&line, &len, w_file) != -1) {
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

  return cat_arr;
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
