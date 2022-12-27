#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LENGTH 8

typedef struct
{
  int lineNumber;
  int lineLength;
} Data;

char *reverse(char *str)
{
  int temp;
  int len = strlen(str);

  for (int i = 0; i < len / 2; i++)
  {
    temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }

  return str;
}

void cleanup(size_t len, char *array[len])
{
  for (size_t i = 0; i < len; i++)
  {
    free(array[i]);
  }
  free(array);
}

void printResult(int lineNumber, size_t len, char *array[len])
{
  for (size_t i = 0; i < len; i++)
  {
    if (lineNumber)
      printf("%zu %s\n", len - i, reverse(array[len - 1 - i]));
    else
      printf("%s\n", reverse(array[len - 1 - i]));
  }
}

void handleFile(char *fileName, Data d)
{
  char **container = malloc(DEFAULT_LENGTH * sizeof(char *));

  FILE *f = fopen(fileName, "r");
  if (f == NULL)
  {
    printf("%s%s\n", "File opening unsuccessful: ", fileName);
    exit(-1);
  }
  char buf[d.lineLength];
  size_t current_length = DEFAULT_LENGTH;
  size_t count = 0;

  while (fgets(buf, d.lineLength, f) != NULL)
  {
    container[count] = malloc(d.lineLength * sizeof(char));
    buf[strcspn(buf, "\n")] = 0;
    strcpy(container[count], buf);

    if (++count == current_length)
    {
      char **temp = realloc(container, (current_length + DEFAULT_LENGTH) * sizeof(char *));
      if (temp == NULL)
      {
        exit(-1);
      }
      container = temp;
      current_length += DEFAULT_LENGTH;
    }
  }

  printResult(d.lineLength, count, container);
  cleanup(count, container);
}

int main(int argc, char *argv[])
{
  if (argc <= 2)
  {
    printf("%s\n", "Usage:\n\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...");
    return 1;
  }

  char *lineNums = argv[1];
  char *lineLength = argv[2];
  if (strcmp(lineNums, "linenums") != 0 && strcmp(lineNums, "nolinenums") != 0)
  {
    printf("%s\n", "error");
    return 1;
  }

  Data d = {(strcmp(lineNums, "linenums") == 0), atoi(lineLength)};

  if (argc > 3)
  {
    for (int i = 3; i < argc; i++)
    {
      char *fileName = argv[i];
      handleFile(fileName, d);
    }
  }

  return 0;
}