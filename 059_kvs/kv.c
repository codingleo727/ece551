#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * input = fopen(fname, "r");
  if (input == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kvset = malloc(sizeof(*kvset));
  if (!kvset) {
    perror("Malloc");
    exit(EXIT_FAILURE);
  }
  kvset->kvpair_array = NULL;
  kvset->length = 0;
  char * line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input) != -1) {
    line[strcspn(line, "\n")] = '\0';

    kvset->kvpair_array =
        realloc(kvset->kvpair_array, (kvset->length + 1) * sizeof(*kvset->kvpair_array));

    char * p = line;

    while (*p != '\0' && *p != '=') {
      p++;
    }

    size_t key_len = 0;
    char * val;

    if (*p == '=') {
      key_len = (size_t)(p - line);
      val = p + 1;
    }
    else {
      key_len = strlen(line);
      val = "";
    }

    kvset->kvpair_array[kvset->length].key = strndup(line, key_len);
    kvset->kvpair_array[kvset->length].value = strdup(val);

    kvset->length++;
  }

  free(line);
  if (fclose(input) != 0) {
    perror("Failed to close file");
    exit(EXIT_FAILURE);
  }

  return kvset;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->kvpair_array[i].key);
    free(pairs->kvpair_array[i].value);
  }
  free(pairs->kvpair_array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n",
           pairs->kvpair_array[i].key,
           pairs->kvpair_array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->kvpair_array[i].key, key) == 0) {
      return pairs->kvpair_array[i].value;
    }
  }
  return NULL;
}
