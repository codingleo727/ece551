#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * input = fopen(fname, "r");
  if (input == NULL) {
    perror("Error opening file\n");
    exit(EXIT_FAILURE);
  }
  
  kvarray_t * kvset = malloc(sizeof(*kvset));
  if (!kvset) {
    perror("Malloc\n");
    exit(EXIT_FAILURE);
  }
  int capacity = 1;
  kvset->kvpair_array = malloc(capacity * sizeof(*kvset->kvpair_array));
  if (!kvset->kvpair_array) {
    perror("Malloc\n");
    exit(EXIT_FAILURE);
  }
  char line[256];
  int len = 0;
  while (fgets(line, sizeof(line), input)) {
    line[strcspn(line, "\n")] = '\0';
   
    if (len == capacity) {
      capacity *= 2;
      kvpair_t * temp = realloc(kvset->kvpair_array, capacity * sizeof(*kvset->kvpair_array));
      if (!temp) {
        perror("Realloc\n");
	exit(EXIT_FAILURE);
      }
      kvset->kvpair_array = temp;
    }

    char * p = line;
    int key_len = 0;
    int value_len = 0; 
    
    while (*p != '=' && *p != '\0') {
      kvset->kvpair_array[len].key[key_len] = *p;
      key_len++;
      p++;
    }
    kvset->kvpair_array[len].key[key_len] = '\0';
    p++;
    
    while (*p != '\0') {
      kvset->kvpair_array[len].value[value_len] = *p;
      value_len++;
      p++;
    }
    kvset->kvpair_array[len].value[value_len] = '\0';
    len++;
  }
  kvset->length = len;
  
  if (fclose(input) != 0) {
    perror("Failed to close file\n");
    exit(EXIT_FAILURE);
  }  

  return kvset;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  free(pairs->kvpair_array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpair_array[i].key, pairs->kvpair_array[i].value); 
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
