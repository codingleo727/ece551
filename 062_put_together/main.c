#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * input = fopen(filename, "r");
  if (input == NULL) {
    perror("Error opening file\n");
    exit(EXIT_FAILURE);
  }  
  char line[256];
  counts_t * counts = createCounts();
  while (fgets(line, sizeof(line), input)) {
    line[strcspn(line, "\n")] = '\0';
    char * value = lookupValue(kvPairs, line);
    addCount(counts, value);
  }
  
  if (fclose(input) != 0) {
    perror("Failed to close file\n");
    exit(EXIT_FAILURE);
  } 

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Input size must be at least 3\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]); 

 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c
  for (int i = 2; i < argc; i++) {
    counts_t * count = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Error opening file\n");
      exit(EXIT_FAILURE);
    }
    printCounts(count, f);
    if (fclose(f) != 0) {
      perror("Failed to close file\n");
      exit(EXIT_FAILURE);
    }
    free(outName);
    freeCounts(count);
  }

 //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
