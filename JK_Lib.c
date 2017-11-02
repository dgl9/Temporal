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
