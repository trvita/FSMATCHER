#pragma once
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define CSI "\x1B\x5B"

void recursion(char *path, int transitionTable[256][256],
               const size_t lenSample, int *findsCounter);
void nonRecursion(char *path, int transitionTable[256][256],
                  const size_t lenSample, int *findsCounter);

void createTable(const char *p, int transitionTable[256][256],
                 const char *hash);
int match(const char *t, int transitionTable[256][256], const size_t lenSample);
void fill(const int n);
void printTable(int transitionTable[256][256], const size_t lenSample,
                const char *hash);