#include <stdio.h>
#include <string.h>
#include "rev.h"

int main(int argc, char *argv[])
{
  if (argc <= 2)
  {
    fprintf(stderr, "Usage:\n\t%s [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...\n", argv[0]);
    return 1;
  }

  char *lineNums = argv[1];
  char *lineLength = argv[2];
  if (strcmp(lineNums, "linenums") != 0 && strcmp(lineNums, "nolinenums") != 0)
  {
    fprintf(stderr, "[SHOW LINE NUMBERS] -> [linenums|nolinenums]\n");
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