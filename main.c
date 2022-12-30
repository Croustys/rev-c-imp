#include <stdio.h>
#include <string.h>
#include "rev.h"

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
      handleInput(argv[i], d);
  }
  else
    handleInput(NULL, d);

  return 0;
}