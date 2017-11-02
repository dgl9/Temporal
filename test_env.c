#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "library.h"

int main() {
  int add[] = {2,3,4,6,5,9};


  cell_matrix * a = newCellMatrix(4,4);

  uniqueAppendToCell(a,1,1,1);
  uniqueAppendToCell(a,1,1,2);
  uniqueAppendToCell(a,1,1,3);
  uniqueAppendToCell(a,1,1,3);
  uniqueAppendToCell(a,4,4,3);
  callback disp = display;

  SetCell(a,2,1,3);
  SetCell(a,2,1,4);
  printCellMatrix(a);
  printCell(a,1,1);

  node * b = create(1,NULL);
  printf("---%i\n", ListLength(b));

  b  = append(b,5);
  printf("---%i\n", ListLength(b));


  node * lst = create(-1,NULL);
  uniqueAppendList(lst,add,6);
  traverse(lst,disp);
  printf("\n");
  traverse(b,disp);
    printf("\n");
  node * z = ismember(b,lst);
  traverse(z,disp);
  printf("\n");
  printf("\n");

  matrix * i = newMatrix(3,3);
  matrix * j = newMatrix(3,3);

  setElement(i,1,1,1);
  setElement(i,2,1,1);
  setElement(i,3,1,1);
  setElement(j,1,1,1);
  setElement(j,2,1,1);
  setElement(j,3,1,1);






  printMatrix(i);
  printf("\n");
  printMatrix(j);
  printf("\n");
  printf("\n");
  node * checkin = ismemberRows(i,j);
  printf("\n\n%i\n\n",nonZeroAmnt(checkin));
  printf("\n\n%i\n\n",ListLength(checkin));

  printf("=====DISTANCE MATRIX TEST======\n");
  matrix * a1 = newMatrix(3,3);
  setElement(a1,1,1,1);
  setElement(a1,2,2,1);
  setElement(a1,3,3,1);
  setElement(a1,1,2,1);
  setElement(a1,2,1,1);

  int TxAdd[] = {2,3,4,6,5,9};
  int TyAdd[] = {2,3,4,6,5,9};
  node * Tx = create(-1,NULL);
  uniqueAppendList(Tx,TxAdd,3);
  node * Ty = create(-1,NULL);
  uniqueAppendList(Ty,TyAdd,3);
  printMatrix(a1);
  DistanceMatrix(a1,Tx,Ty,10000);
  return 0;
}
