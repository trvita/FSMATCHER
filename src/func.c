#include "func.h"

char colors[][5] = {"0;30", /* Blacstate*/ "1;30", /* DarstateGray */
                    "0;31", /* Red */ "1;31",      /* Bold Red */
                    "0;32", /* Green */ "1;32",    /* Bold Green */
                    "0;33", /* Yellow */ "1;33",   /* Bold Yellow */
                    "0;34", /* Blue */ "1;34",     /* Bold Blue */
                    "0;35", /* Purple */ "1;35",   /* Bold Purple */
                    "0;36", /* Cyan */ "1;36" /*Bold Cyan */};
int match(const char *text, int transitionTable[256][256],
          const size_t lenSample) {
  size_t lenText = strlen(text);
  size_t finalState = 0, currentState = 0, i;
  for (i = 0; i < lenText; i++) {
    char symbol = text[i];
    finalState = transitionTable[currentState][(int)symbol];
    currentState = transitionTable[currentState][(int)symbol];
    if (finalState == lenSample)
      return (i - lenSample + 2); // index of find i - lenSample +2
  }
  return -1;
}

void recursion(char *path, int transitionTable[256][256],
               const size_t lenSample, int *findsCounter) {
  char *fpath = (char *)calloc(sizeof(char), 256);
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      char *fileName = (char *)calloc(sizeof(char), 256);
      strcpy(fileName, ent->d_name);
      int matchIndex = match(fileName, transitionTable, lenSample);
      if (matchIndex >= 0) {
        printf("%s%sm%20s%s0m - ", CSI, colors[3], fileName, CSI);
        *findsCounter += 1;
      } else
        printf("%20s - ", fileName);
      if (ent->d_type == DT_REG) {
        printf("file\n");
      } else {
        if ((ent->d_type == DT_DIR) && (strcmp(fileName, ".") != 0) &&
            (strcmp(fileName, "..") != 0)) {
          printf("directory\n");
          strcpy(fpath, path);
          fpath = strcat(fpath, "/");
          fpath = strcat(fpath, fileName);
          recursion(fpath, transitionTable, lenSample, findsCounter);
        } else
          printf("other type\n");
      }
      free(fileName);
    }
    closedir(dir);
    free(fpath);
  } else {
    closedir(dir);
    printf("There is no such directoty\n");
    return;
  }
}

void nonRecursion(char *path, int transitionTable[256][256],
                  const size_t lenSample, int *findsCounter) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      char *fileName = (char *)calloc(sizeof(char), 256);
      strcpy(fileName, ent->d_name);
      int matchIndex = match(fileName, transitionTable, lenSample);
      if (matchIndex >= 0) {
        printf("%s%sm%20s%s0m - ", CSI, colors[3], fileName, CSI);
        *findsCounter += 1;
      } else
        printf("%20s - ", fileName);
      if (ent->d_type == DT_REG) {
        printf("file\n");
      } else {
        printf("directory\n");
      }
      free(fileName);
    }
    closedir(dir);
  } else {
    closedir(dir);
    printf("There is no such directoty\n");
    return;
  }
}

void createTable(const char *sample, int transitionTable[256][256],
                 const char *hash) {
  size_t lenSample = strlen(sample);
  size_t i, j;
  for (i = 0; i <= lenSample; i++) {
    for (j = 1; j <= 255; j++) {
      if (hash[j]) {
        int state = 0;
        if (lenSample >= i + 1)
          state = i + 1;
        else
          state = lenSample;
        while (state > 0) {
          state = state - 1;
          char symbol = sample[state];
          if ((state >= 0) && ((size_t)symbol == j)) {
            int suffix = state, prefix = i;
            while ((suffix > 0) && (sample[suffix] == sample[prefix])) {
              suffix = suffix - 1;
              prefix = prefix - 1;
            }

            if (suffix == 0) {
              state++;
              break;
            }
          }
        }
        transitionTable[i][j] = state;
      }
    }
  }
}

void fill(const int n) {
  for (int i = 0; i <= n; i++)
    printf("─");
}

void printTable(int transitionTable[256][256], const size_t lenSample,
                const char *hash) {
  printf("Transition table:\n");
  size_t t = lenSample;
  size_t i, j, digits = 0;
  while (t > 0) {
    digits = digits;
    t = t / 10;
  }
  printf("┌");
  printf("─");
  for (j = 0; j <= lenSample; j++) {
    printf("┬");
    fill(digits + 1);
  }
  printf("┐\n");
  printf("│δ");
  for (i = 0; i <= lenSample + digits; i++)
    printf("│ %ld", i);
  printf("│\n");
  for (i = 1; i <= 255; i++) {
    if (hash[i]) {
      printf("├─");
      for (j = 0; j <= lenSample; j++) {
        printf("┼");
        fill(digits + 1);
      }
      printf("┤\n");
      char c = i;
      printf("│%c", c);
      for (j = 0; j <= lenSample; j++)
        printf("│ %d", transitionTable[j][i]);
      printf("│\n");
    }
  }
  printf("└");
  printf("─");
  for (j = 0; j <= lenSample; j++) {
    printf("┴");
    fill(digits + 1);
  }
  printf("┘\n");
  printf("\n");
}
