#include "func.h"

int main(int argc, char **argv) {
  char colors[][5] = {"0;30", /* Black */ "1;30",  /* Dark Gray */
                      "0;31", /* Red */ "1;31",    /* Bold Red */
                      "0;32", /* Green */ "1;32",  /* Bold Green */
                      "0;33", /* Yellow */ "1;33", /* Bold Yellow */
                      "0;34", /* Blue */ "1;34",   /* Bold Blue */
                      "0;35", /* Purple */ "1;35", /* Bold Purple */
                      "0;36", /* Cyan */ "1;36" /*Bold Cyan */};
  char hash[256];
  size_t i, j, recurs;

  if ((strcmp(argv[1], "-r") == 0) && argc == 4) {
    printf("Recursive search of '%s%sm%s%s0m' in directory %s%sm%s%s0m\n", CSI,
           colors[2], argv[2], CSI, CSI, colors[3], argv[3], CSI);
    recurs = 1;
  } else {
    if ((argc == 3) && ((strcmp(argv[1], "-r") != 0))) {
      printf("Search of '%s%sm%s%s0m' in directory %s%sm%s%s0m\n", CSI,
             colors[2], argv[1], CSI, CSI, colors[3], argv[2], CSI);
      recurs = 0;
    } else {
      if (argc == 3) {
        printf("Invalid number of arguments entered\n");
        return -1;
      } else {
        printf("Invalid option entered\n");
        return -2;
      }
    }
  }
  size_t temp = strlen(argv[2 + recurs]);
  if (temp > 256) {
    printf("Length of directory name is above 256\n");
    return -3;
  }
  temp = strlen(argv[1 + recurs]);
  if (temp > 256) {
    printf("Length of sample is above 256\n");
    return -4;
  }
  temp = strlen(argv[1 + recurs]);
  if (temp < 1) {
    printf("The sample is empty\n");
    return -5;
  }
  char *dir1 = (char *)calloc(sizeof(char), 256);
  if (!dir1)
    return -7;
  char *sample = (char *)calloc(sizeof(char), 256);
  if (!sample)
    return -7;

  for (i = 0; i < strlen(argv[2 + recurs]); i++) {
    dir1[i] = (argv[2 + recurs])[i];
  }
  for (i = 0; i < strlen(argv[1 + recurs]); i++) {
    sample[i] = (argv[1 + recurs])[i];
  }

  size_t lenSample = strlen(sample);
  int findsCounter = 0;
  int *counter;
  counter = &findsCounter;
  int transitionTable[256][256];
  DIR *dir;
  if ((dir = opendir(dir1)) == NULL) {
    printf("There is no such directory\n");
    closedir(dir);
    return -6;
  }

  memset(transitionTable, 0, sizeof(transitionTable));
  memset(hash, 0, sizeof(hash));

  for (j = 0; j < lenSample; j++) {
    char symbol = sample[j];
    hash[(int)symbol] = 1;
  }

  createTable(sample, transitionTable, hash);
  printTable(transitionTable, lenSample, hash);
  if (recurs == 1) {
    recursion(dir1, transitionTable, lenSample, counter);
  } else {
    nonRecursion(dir1, transitionTable, lenSample, counter);
  }
  if (findsCounter == 0) {
    printf("No matching for '%s%sm%s%s0m' found\n", CSI, colors[3], sample,
           CSI);
  } else
    printf("%s%sm%d%s0m matches found for '%s%sm%s%s0m'\n", CSI, colors[3],
           findsCounter, CSI, CSI, colors[3], sample, CSI);
  closedir(dir);
  free(sample);
  free(dir1);
  return 0;
}
