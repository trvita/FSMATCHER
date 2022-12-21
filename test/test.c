#include "func.h"
#include <ctest.h>
#include <stdio.h>

CTEST(match_suite, right) {
  // Given
  const char sample[] = {'a'};
  const size_t len = strlen(sample);
  int tTable[256][256];
  char hash[256];
  memset(tTable, 0, sizeof(tTable));
  memset(hash, 0, sizeof(hash));
  for (size_t j = 0; j < len; j++) {
    char symbol = sample[j];
    hash[(int)symbol] = 1;
  }
  createTable(sample, tTable, hash);

  // When
  const int result = match(sample, tTable, len);
  // Then
  const int unexpected = -1;
  ASSERT_NOT_EQUAL(unexpected, result);
}

CTEST(match_suite, wrong) {
  // Given
  const char sample[] = {'a', 'b'};
  const char wrong[] = {'q', 'q', 'q'};
  const size_t len = strlen(sample);
  int tTable[256][256];
  char hash[256];
  memset(tTable, 0, sizeof(tTable));
  memset(hash, 0, sizeof(hash));

  for (size_t j = 0; j < len; j++) {
    char symbol = sample[j];
    hash[(int)symbol] = 1;
  }

  createTable(sample, tTable, hash);

  // When
  const int result = match(wrong, tTable, len);
  // Then
  const int expected = -1;
  ASSERT_EQUAL(expected, result);
}