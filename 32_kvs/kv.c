#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"




// split curr to key and value, then form kvpair_t
kvpair_t * getKeyValue(char * line) {
  char * division = strchr(line, '=');
  if (division == NULL) {
    fprintf(stderr, "key, value format error.");
    exit(EXIT_FAILURE);
  }
  char * p = strchr(line, '\n');
  *division = '\0';
  *p = '\0';
  kvpair_t * kvpair = malloc(sizeof(*kvpair));
  if (kvpair == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  kvpair->key = line;
  kvpair->value = division + 1;
  return kvpair;
}

void appendKeyValue(kvpair_t *** kvpairs_p, size_t * numkvpair_p, kvpair_t * kvpair) {
  *kvpairs_p = realloc(*kvpairs_p, (++(*numkvpair_p)) * sizeof(kvpair_t *));
  if (*kvpairs_p == NULL) {
    perror("realloc error");
    exit(EXIT_FAILURE);
  }
  (*kvpairs_p)[*numkvpair_p - 1] = kvpair;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open the file");
    exit(EXIT_FAILURE);
  }
  size_t numkvpairs = 0;
  kvpair_t ** kvpairs = NULL;
  char * curr = NULL;
  size_t sz = 0;
  while (getline(&curr, &sz, f) > 0) {
    appendKeyValue(&kvpairs, &numkvpairs, getKeyValue(curr));
    curr = NULL;
    sz = 0;
  }
  free(curr);

  if (fclose(f) != 0) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }

  kvarray_t * pairs = malloc(sizeof(*pairs));
  if (pairs == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  pairs->numkvpairs = numkvpairs;
  pairs->kvpairs = kvpairs;
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t * pair = pairs->kvpairs[i];
    // watch out! pair->key was malloced in getline, and it is the start.
    // pair->value is not the start, and been freed with free(pair->key)
    free(pair->key);
    free(pair);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t * pair = pairs->kvpairs[i];
    printf("key = '%s' value = '%s'\n", pair->key, pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t * pair = pairs->kvpairs[i];
    if (strcmp(key, pair->key) == 0) {
      return pair->value;
    }
  }
  return NULL;
}
