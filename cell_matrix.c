#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_buchi.h"

typedef struct{
  int rows;
  int cols;
  node ** data;
} cell_matrix;

cell_matrix * newCellMatrix(int rows, int cols);
int deleteCellMatrix(cell_matrix * mtx);

#define CELL(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

cell_matrix * copyCellMatrix(cell_matrix * mtx); //copies one matrix into another
int setCell(cell_matrix * mtx, int row, int col, int val);
node * getCell(cell_matrix * mtx, int row, int col);
int printCellMatrix(cell_matrix * mtx);
void printCell(cell_matrix * mtx, int row, int col);
void AppendToCell(cell_matrix * mtx, int row, int col, int val);
void uniqueAppendToCell(cell_matrix * mtx, int row, int col, int val);
void SetCell(cell_matrix * mtx, int row, int col, int val);
int ListLength(node * head);
void uniqueAppendList(node * head, int * nums, int amnt);
node * ismember(node * in, node * out);
int isempty(node* head);

int main() {
  /* code */
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



  return 0;


}

node * ismember(node * in, node * out){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->next = NULL;
  node * temp = in;
  int count = 0;
  while((temp)){
    int x = (searchInd(out, temp->data));
    if(x){
      if(count == 0){
        new_node->data = x;
        new_node->next = NULL;
      }
      else{
        new_node = append(new_node,x);
      }
    }
    temp = temp->next;
    count++;
  }
  return new_node;
}


int isempty(node* head){
  if(head){
    return 0;
  }
  return 1;
}


cell_matrix * newCellMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) return NULL;

  // allocate a matrix structure
  cell_matrix * m = (cell_matrix *) malloc(sizeof(cell_matrix));

  // set dimensions
  m->rows = rows;
  m->cols = cols;

  // allocate a int array of length rows * cols
  m->data = (node **) malloc(rows*cols*sizeof(node*));
  // set all data to NULL
  int i;
  for (i = 0; i < rows*cols; i++)
    m->data[i] = NULL;

  return m;
}

int deleteCellMatrix(cell_matrix * mtx) {
  if (!mtx) return -1;
  // free mtx's data
  assert (mtx->data);
  free(mtx->data);
  // free mtx itself
  free(mtx);
  return 0;
}



cell_matrix * copyCellMatrix(cell_matrix * mtx) {
  if (!mtx) return NULL;

  // create a new matrix to hold the copy
  cell_matrix * cp = newCellMatrix(mtx->rows, mtx->cols);

  // copy mtx's data to cp's data
  memcpy(cp->data, mtx->data,
         mtx->rows * mtx->cols * sizeof(int));

  return cp;
}




void AppendToCell(cell_matrix * mtx, int row, int col, int val){
  if(CELL(mtx,row,col)!=NULL){
    CELL(mtx,row,col) = append(CELL(mtx,row,col),val);
  }
  else{
    CELL(mtx,row,col) = create(val,NULL);
  }
}

void SetCell(cell_matrix * mtx, int row, int col, int val){
  dispose(CELL(mtx,row,col));
  CELL(mtx,row,col) = create(val,NULL);
}


void uniqueAppendToCell(cell_matrix * mtx, int row, int col, int val){
  if(CELL(mtx,row,col)!=NULL){
    if (search(CELL(mtx,row,col),val) == NULL){
      CELL(mtx,row,col) = append(CELL(mtx,row,col),val);
    }
  }
  else{
    CELL(mtx,row,col) = create(val,NULL);
  }
}

void uniqueAppendList(node * head, int * nums, int amnt){
  if(!nums) return;
  int * temp = nums;
  if (!(head->next) && (head->data == -1)){
    head->data = *temp;
    temp++;
    amnt--;
  }
  for(int i = 0; i < amnt; i++){
    if(!search(head,*temp)){
      head = append(head,*temp);
    }
    temp++;
  }
}

node * getCell(cell_matrix * mtx, int row, int col) {
  if (!mtx) return NULL;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return NULL;

  return CELL(mtx, row, col);
}

int printCellMatrix(cell_matrix * mtx) {
  if (!mtx) return -1;
  callback disp = display;
  int row, col;
  node * temp;
  for (row = 1; row <= mtx->rows; row++) {
    for (col = 1; col <= mtx->cols; col++) {
      // Print the floating-point element with
      //  - either a - if negative or a space if positive
      //  - at least 3 spaces before the .
      //  - precision to the hundredths place
      printf("Row: %i \nCol: %i \n",row, col);
      traverse(getCell(mtx,row,col),disp);
      printf("\n");
    }
    // separate rows by newlines
    printf("\n");
  }
  return 0;
}

void printCell(cell_matrix * mtx, int row, int col){
  callback disp = display;
  printf("Row: %i \nCol: %i \n",row, col);
  traverse(getCell(mtx,row,col),disp);
  printf("\n");
}

int ListLength(node * head){
  int len = 0;
  while((head=head->next)){
    len++;
  }
  return len;
}
