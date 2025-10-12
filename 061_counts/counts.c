#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->size = 0;
  counts->names = NULL;
  counts->count_unknown = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->count_unknown++;
    return;
  }
  int comp = 1;
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(c->names[i].name, name) == 0) {
      c->names[i].num++;
      comp = 0;
      break;
    }
  }

  if (comp == 1) {
    c->names = realloc(c->names, (c->size + 1) * sizeof(*c->names));
    c->names[c->size].name = strdup(name);
    c->names[c->size].num = 1;
    c->size++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->names[i].name, c->names[i].num);
  }

  if (c->count_unknown > 0) {
    fprintf(outFile, "<unknown>: %d\n", c->count_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->names[i].name);
  }
  free(c->names);
  free(c);
}
