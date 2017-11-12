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
  node * new_node = (node *)malloc(sizeof(node));
  new_node->next = NULL;
  for(int i = 1; i <= A->rows; i++){
    int loc = 0;
    for(int j = 1; j <= B->rows; j++){
      if(check_row(A,B,i,j) && loc == 0) {
        loc = j;
      }
    }

    if(i == 1){
      printf("%i\n", loc);
      new_node = create(loc,NULL);
    }
    else{
      printf("%i\n", loc);
      new_node = append(new_node,loc);
    }
  }
  return new_node;

}

node * cost(matrix * qpts, int N, node * xNew, matrix * dist, int bigNumber) {
  int rows = qpts->rows;
  int cols = qpts->cols;
  cost = newMatrix(rows, 1);

  // for every robot (1 to N), find the cost in the corresponding distance matrix and update the cost vector
  for (int i = 1; i <= N; i++)
  {
    cost = cost + dist(getLinkedElement(xNew, i), qpts(:, i));
  }

  // find the minimum cost in the cost vector
  minCost = matrix_Minimum(cost);

  if (minCost >= bigNumber) {
    // then not feasible transition in the PTS (what does this mean)

  }
}

int matrix_Minimum(matrix * myMatrix)
{
   int min = ELEM(myMatrix, 0, 0);
   int rows = myMatrix->rows;
   int cols = myMatrix->cols;
   for (int x = 0; x < rows; x++)
   {
       for (int y = 0; y < cols; y++)
       {
           if (min > ELEM(myMatrix, x, y)
           {
               min = ELEM(myMatrix, x, y);
           }
       } 
   }  
   return min;
}

