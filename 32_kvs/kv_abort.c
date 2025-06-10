#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void stripNewline(char * str) {
  char *p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

int containValue(char * value, kvpair_t ** pairs_list, int * list_num) {
  for (int i = 0; i < *list_num; i++) {
    if (strcmp(pairs_list[i]->value, value) == 0) {
      return 1;
    }
  }
  return 0;
}

void process_keys_by_value(kvpair_t ** pairs_list, int * list_num,
                           char * value, char * key) {
  int vindex = -1;
  for (int i = 0; i < *list_num; i++) {
    if (strcmp(pairs_list[i]->value, value) == 0) {
      vindex = i;
      break;
    }
  }
  if (vindex == -1) {
    return;
  }

  for (int j = 0; j < pairs_list[vindex]->key_num; j++) {
    if (strcmp(pairs_list[vindex]->key_list[j], key) == 0) {
      return;
    }
  }

  int key_num = pairs_list[vindex]->key_num;
  char ** key_list = pairs_list[vindex]->key_list;
  key_list = realloc(key_list, (key_num + 1) * sizeof(*key_list));
  key_list[key_num] = key;
  pairs_list[vindex]->key_num = key_num + 1;
  return;
}

void add_new_kvpair(kvpair_t *** pairs_list, int * list_num,
                    char * value, char * key) {
  kvpair_t ** new_list = realloc(*pairs_list, (*list_num + 1) * sizeof(kvpair_t *));
  *pairs_list = new_list;
  kvpair_t * newPair = malloc(sizeof(*newPair));
  newPair->value = value;
  newPair->key_num = 1;
  newPair->key_list = malloc(sizeof(char *));
  newPair->key_list[0] = key;
  (*pairs_list)[*list_num] = newPair;
  *list_num = *list_num + 1;
}

void process_vks_pairs_list(char * curr, kvpair_t *** vks_pairs_list,
                            int * list_num) {
  char * value_ptr = strchr(curr, '=');
  if (value_ptr == NULL) {
    return;
  }
  char * value = strdup(value_ptr + 1);
  * value_ptr = '\0';
  stripNewline(value);
  char * key = strdup(curr);
  if (containValue(value, *vks_pairs_list, list_num) == 1) {
    process_keys_by_value(*vks_pairs_list, list_num, value, key);
    free(value);
  }
  else {
    add_new_kvpair(vks_pairs_list, list_num, value, key);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Can not open the file\n");
    return NULL;
  }
  kvarray_t * res = malloc(sizeof(*res));
  if (res == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  res->vks_pairs_num = 0;
  res->vks_pairs_list = NULL;

  char * curr = NULL;
  size_t sz = 0;
  while((getline(&curr, &sz, f)) >= 0) {
    process_vks_pairs_list(curr, &(res->vks_pairs_list), &(res->vks_pairs_num));
    curr = NULL;
  }
  free(curr);
  fclose(f);
  return res;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
}
