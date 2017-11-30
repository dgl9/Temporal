#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "library.h"



node* ismemberRows(matrix * A, matrix * B){
  if(A->cols != B->cols){
    return NULL;
  }
  node * result = NULL;
  int noRes = 1;
  int loc = 0;
  for(int i = 1; i <= A->rows; i++){
    loc = 0;
    for(int j = 1; j <= B->rows; j++){
      if(check_row(A,B,i,j) && loc == 0) {
        loc = j;
      }
    }
    if(loc){
      result = append(result,loc);
      noRes = 0;
    }
    else{
      result = append(result,0);
    }
  }
  if(noRes){
    dispose(result);
    return NULL;
  }
  return result;

}

int costTree(int start, int end, matrix * Dist, matrix * Qpba){
  int cost = 0;
  int state_start;
  int state_end;
  for(int i = 1; i <= Qpba->cols -1; i++){
    state_start = ELEM(Qpba,start,i);
    state_end = ELEM(Qpba,end,i);
    cost += ELEM(Dist,state_start,state_end);
  }

  return cost;
}


int findPrevPTSpoint(matrix * QPTS,node * xNew,matrix * Dist,int BigNum, matrix * CostNode, node*indices){
  int min_cost = 2147483647;
  int min_ind;
  int temp_cost;
  int temp_ind;
  int xNewState;
  int QptsState;
  for(int row = 1; row <= QPTS->rows; row++){
    temp_ind = getLinkedElement(indices,row);
    temp_cost = ELEM(CostNode,temp_ind,1);
    for(int rbt = 1; rbt <= ListLength(xNew); rbt++){
      xNewState = getLinkedElement(xNew,rbt);
      QptsState = ELEM(QPTS,row,rbt);
      temp_cost += ELEM(Dist,QptsState,xNewState);
    }
    if (temp_cost < min_cost){
      min_cost = temp_cost;
      min_ind = row;
    }
  }
  if(min_cost >= BigNum){
    return 0;
  }
  return min_ind;
}
