#include <stdio.h>
#include <stdlib.h>

void printHelp(char *name) {
  printf("usage: %s N M S\n", name);
  printf("Print elements of sequence\n");
  printf("arguments:\n");
  printf("N – number of the beginning of the sequence. Default is `0`");
  printf("M – number of the ending of the sequnce, but not including it");
  printf("S – difference between each number of sequence. Default is `1`");
}

void range(int beg, int end, int step) {
  for (int i = beg; i < end; i += step)
    printf("%d\n", i);
}

int main(int argc, char **argv) {
  int end, beg, step;

  switch (argc) {
  case 2:
    end = atoi(argv[1]);
    range(0, end, 1);
    break;

  case 3:
    beg = atoi(argv[1]);
    end = atoi(argv[2]);
    range(beg, end, 1);
    break;

  case 4:
    beg = atoi(argv[1]);
    end = atoi(argv[2]);
    step = atoi(argv[3]);
    range(beg, end, step);
    break;

  default:
    printHelp(argv[0]);
  }

  return 0;
}
