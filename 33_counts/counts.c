#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  if (counts == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  counts->countsArray = NULL;
  counts->countNum = 0;
  counts->unknowCount = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknowCount++;
    return;
  }
  one_count_t ** countsArray = c->countsArray;
  for(int i = 0; i < c->countNum; i++) {
    if(strcmp(countsArray[i]->name, name) == 0) {
      countsArray[i]->count += 1;
      return;
    }
  }
  // name does not exist
  one_count_t ** newCountsArray = realloc(countsArray, (c->countNum + 1) *
                                          sizeof(one_count_t *));
  if (newCountsArray == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  c->countNum += 1;
  c->countsArray = newCountsArray;

  one_count_t * newOneCount = malloc(sizeof(*newOneCount));
  if (newOneCount == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  // copy name to a new allocated block!.
  // strlen do not count '\0'
  char * newName = malloc((strlen(name) + 1) * sizeof(*newName));
  if (newName == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  strcpy(newName, name);
  // assign values
  newOneCount->name = newName;
  newOneCount->count = 1;
  newCountsArray[c->countNum - 1] = newOneCount;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  one_count_t ** countsArray = c->countsArray;
  for (int i = 0; i < c->countNum; i++) {
    fprintf(outFile, "%s: %d\n", countsArray[i]->name, countsArray[i]->count);
  }
  if (c->unknowCount > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknowCount);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  one_count_t ** countsArray = c->countsArray;
  for (int i = 0; i < c->countNum; i++) {
    // newName above is allocated
    free(countsArray[i]->name);
    free(countsArray[i]);
  }
  free(countsArray);
  free(c);
}
