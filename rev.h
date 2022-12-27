#ifndef REV_H
#define REV_H

#include <stdlib.h>

#define DEFAULT_LENGTH 8

typedef struct
{
  int lineNumber;
  int lineLength;
} Data;

char *reverse(char *str);
void cleanup(size_t len, char *array[]);
void printResult(int lineNumber, size_t len, char *array[]);
void handleFile(char *fineName, Data d);
#endif