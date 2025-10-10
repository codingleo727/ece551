#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  if (!inputName) {
    fprintf(stderr, "Input name is NULL\n");
    exit(EXIT_FAILURE);
  }
  
  char input[strlen(inputName) + 1];
  strncpy(input, inputName, strlen(inputName) + 1);
  char * suffix = ".count";
  int suffix_len = strlen(suffix);
  char * output = malloc(suffix_len + strlen(inputName) + 1);
  char * p = input;
  int i = 0;
  while (*p != '\0') {
    output[i] = *p;
    i++;
    p++;
  }
  int j = 0;
  while (*suffix != '\0') {
    output[j + strlen(inputName)] = *suffix;
    j++;
    suffix++;
  }

  output[suffix_len + strlen(inputName)] = '\0';

  return output;
}
