#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "library.h"



matrix * DistanceMatrix(matrix * Trans, node * Tx, node * Ty, int BigNum){
  int rows = Trans->rows;
  int cols = Trans->cols;
  int locs = rows;
  int xLen = ListLength(Tx);
  int yLen = ListLength(Ty);
  if((rows != cols) | (xLen != yLen) | (rows!=xLen)){
    return NULL;
  }
  matrix * dist = newMatrix(locs,locs);
  for(int i = 1; i <= locs; i++){
    for(int j = 1; j <= locs; j++){
      int temp_dist = 0;
      int x1 = getLinkedElement(Tx,i);
      int y1 = getLinkedElement(Ty,i);
      int x2 = getLinkedElement(Tx,j);
      int y2 = getLinkedElement(Ty,j);
      printf("Loc1 : %i Loc2 : %i\nX1 : %i Y1 : %i\nX2 : %i Y2 : %i\n", i,j,x1,y1,x2,y2);
      if(CELL(Trans,i,j) == 0){
        CELL(dist,i,j) = BigNum;
      }
      else{
        CELL(dist,i,j) = (int)(CELL(Trans,i,j) * (pow( pow((x1-x2),2) + pow((y1-y2),2) , 0.5 )));
      }
      printf("Distance : %i\n\n", (int)(CELL(Trans,i,j) * (pow(pow((x1-x2),2) + pow((y1-y2),2), 0.5 ))));
    }
  }
  return dist;

}




node * BuildQPREV(matrix * QPTS,matrix * QB,int prevQPBAindex){
  node * result = NULL;
  for(int i = 1; i <= QPTS->cols; i++){
    result = append(result, ELEM(QPTS,prevQPBAindex,i));
  }
  result = append(result, ELEM(QB,prevQPBAindex,1));
  return result;

}

matrix * BuildQNEXT(node * xNew, int QbNext, int N){
  matrix * QNext = newMatrix(1,N+1);
  for(int z = 1; z <= N; z++){
    ELEM(QNext,1,z) = getLinkedElement(xNew,z);
  }
  ELEM(QNext,1,N+1) = QbNext;
  return QNext;
}

matrix * linkedToMatrix(node* linked){
  matrix * result = newMatrix(1,ListLength(linked));
  node * temp = linked;
  for(int i = 1; i <= ListLength(linked); i++){
    ELEM(result,1,i) = temp->data;
    temp=temp->next;
  }
  return result;
}
