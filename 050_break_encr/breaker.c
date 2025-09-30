#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char maxFrequency(FILE * filename) {
  int c;
  int freq[26] = {0};
  int index = 0;
  int max_val = 0;
  while ((c = fgetc(filename)) != EOF) {
    if (isalpha((unsigned char)c)) {
      c = tolower((unsigned char)c);
      freq[c - 'a']++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (freq[i] > max_val) {
      index = i;
      max_val = freq[i];
    }
  }
  return index + 'a';
}

int calculateKey(FILE * filename) {
  char target = maxFrequency(filename);
  return (target - 'e' + 26) % 26;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please only input the text file for decryption");
    return EXIT_FAILURE;
  }

  FILE * input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  printf("%d\n", calculateKey(input));

  if (fclose(input) != 0) {
    perror("Failed to close input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
