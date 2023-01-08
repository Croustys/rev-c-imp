#include <stdio.h>
#include <string.h>
#include "rev.h"

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
    char *reversed = reverse(array[len - 1 - i]);

    if (lineNumber)
      printf("%zu %s\n", len - i, reversed);
    else
      printf("%s\n", reversed);
  }
}
void handleInput(const char *fileName, Data d)
{
  char **container = malloc(DEFAULT_LENGTH * sizeof(char *));
  if (container == NULL)
  {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(-1);
  }

  FILE *f;
  if (fileName != NULL)
  {
    f = fopen(fileName, "r");
    if (f == NULL)
    {
      fprintf(stderr, "File opening unsuccessful: <%s>\n", fileName);
      exit(-1);
    }
  }
  else
    f = stdin;

  char buf[d.lineLength + 1];
  size_t current_length = DEFAULT_LENGTH;
  size_t count = 0;

  while (fgets(buf, 50, f) != NULL)
  {
    int length = strlen(buf);
    if (length >= d.lineLength)
    {
      buf[d.lineLength] = 0;
    }
    container[count] = malloc(d.lineLength * sizeof(char));
    buf[strcspn(buf, "\n")] = 0;
    strcpy(container[count], buf);

    if (++count == current_length)
    {
      char **temp = realloc(container, (current_length + DEFAULT_LENGTH) * sizeof(char *));
      if (temp == NULL)
      {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
      }
      container = temp;
      current_length += DEFAULT_LENGTH;
    }
  }
  fclose(f);

  printResult(d.lineNumber, count, container);
  cleanup(count, container);
}
