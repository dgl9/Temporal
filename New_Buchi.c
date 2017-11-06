#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "library.h"

int main() {
  callback disp = display;
  int N_p = 7;
  Buchi * x;
  FILE *stream;
  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int sn_count = getStateNames(stream, BUCH_AUT, STATE_NAMES);
  x = Buchi_Struct();
  printf("\n\n\n\n");
  printCellMatrix(x->Trans);
  printf("\n\n\n\n");
  traverse(x->S0,disp);
  printf("\n\n\n\n");
  traverse(x->S,disp);
  printf("\n\n\n\n");
  traverse(x->F,disp);

  return 0;
}
