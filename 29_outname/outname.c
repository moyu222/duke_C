#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  // WRITE ME
  /* // outfileNAme is argv[2] + ".txt", so add 4 to its length. */
  /* char *outFileName = malloc((strlen(argv[2]) + 5) * sizeof(*outFileName)); */
  /* if (outFileName == NULL) { */
  /*   perror("malloc failed"); */
  /* } */
  /* strcpy(outFileName, argv[2]); */
  /* strcat(outFileName, ".enc"); */
  /* FILE *outFile = fopen(outFileName, "w"); */
  char * outfileName = malloc((strlen(inputName) + 8) * sizeof(*outfileName));
  if (outfileName == NULL) {
    perror("malloc failed.");
  }
  strcpy(outfileName, inputName);
  strcat(outfileName, ".counts");
  return outfileName;
}
