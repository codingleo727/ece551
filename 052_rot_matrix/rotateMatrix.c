#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10], char rotated[10][10]) {
  int k = 0;
  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      rotated[j][i] = matrix[k][j];
    }
    k++;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please only input the text file for rotation");
    return EXIT_FAILURE;
  }

  FILE * input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char original[10][10];
  char rotated[10][10];
  char row[128];
  int row_count = 0;
  while (fgets(row, sizeof(row), input)) {
    row[strcspn(row, "\n")] = '\0';
    if (strlen(row) != 10) {
      fprintf(stderr, "Please input a 10x10 matrix");
      return EXIT_FAILURE;
    }

    for (int i = 0; i < 10; i++) {
      original[row_count][i] = row[i];
    }
    row_count++;
  }

  if (row_count != 10) {
    fprintf(stderr, "Please input a 10x10 matrix");
    return EXIT_FAILURE;
  }

  rotate(original, rotated);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", rotated[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(input) != 0) {
    perror("Failed to close input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
