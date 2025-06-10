#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  char * curr = NULL;
  size_t sz = 0;
  while(getline(&curr, &sz, f) > 0) {
    char * p = strchr(curr, '\n');
    *p = '\0';
    addCount(counts, lookupValue(kvPairs, curr));
  }
  free(curr);

  if (fclose(f)) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Usage: ./count_values input1.txt input2.txt ..");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    char *filename = argv[i];
    counts_t *counts = countFile(filename, kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(filename);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(counts, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(counts);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
