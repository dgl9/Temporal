#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "library.h"





//----------------------------------------------------------

node * observeInDiscreteEnvironment(int N, int N_p, cell_matrix * AP, node * xNew,int epsilon){
  node * sat = NULL;
  node * robots;
  int checkAP;
  int rbt;
  for(int ap = 1; ap <= N_p; ap++){
    robots = getCell(AP,ap,N+2);
    checkAP = 0;
    for(int indexRbt = 1; indexRbt <= ListLength(robots); indexRbt ++){
      rbt = getLinkedElement(robots,indexRbt);
      if(getLinkedElement(xNew,rbt) == getCell(AP,ap,rbt)->data){
        checkAP ++;
      }
    }
    if(checkAP == ListLength(robots)){
      sat = append(sat,getCell(AP,ap,N+1)->data);
    }

  }
  if(!sat){
    sat = append(sat,pow(2,N_p));
  }
  return sat;
}

node * sampleReachablePTSpointTree(matrix * Qpba, int N, matrix * Tadj, node * Tx, node * Ty, node * TQ,int ind){
  node * xRand = NULL;
  callback disp = display;
  int pickInd = (rand()%(ind-1)) + 1;
  printf("%i\n", pickInd);
  node * reachable = NULL;
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      if(CELL(Tadj,i,j)){
        reachable = append(reachable,j);
      }
    }
    traverse(reachable,disp);
    xRand = append(xRand, getLinkedElement(reachable,rand()%ListLength(reachable) + 1));
    dispose(reachable);
  }
  printf("\n\n\n");
  traverse(xRand,disp);
  return xRand;

}




int nonZeroAmnt(node * in){
  node * temp = in;
  int count = 0;
  for(int i = 0; i < ListLength(in); i++){
    if(temp->data != 0){
      count++;
    }
    temp = temp->next;
  }
  return count;
}




int check_row(matrix * A, matrix * B, int rowA, int rowB){
  int row_equal = 1;
  for(int i = 1; i <= A->cols; i++){
    if(CELL(A,rowA,i) != CELL(B,rowB,i)){
      row_equal = 0;
    }
  }
  return row_equal;
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


node * AppendList(node * head, int * nums, int amnt){
  if(!nums) return NULL;
  int * temp = nums;
  for(int i = 0; i < amnt; i++){
    head = append(head,*temp);
    temp++;
  }
  return head;
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
  int len = 1;
  while((head=head->next)){
    len++;
  }
  return len;
}














//----------------------------------------------------------

matrix * newMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) return NULL;

  // allocate a matrix structure
  matrix * m = (matrix *) malloc(sizeof(matrix));

  // set dimensions
  m->rows = rows;
  m->cols = cols;

  // allocate a int array of length rows * cols
  m->data = (int *) malloc(rows*cols*sizeof(int));
  // set all data to 0
  int i;
  for (i = 0; i < rows*cols; i++)
    m->data[i] = 0;

  return m;
}

matrix * kronProd(matrix * A, matrix * B){
  int rows_a = A->rows;
  int cols_a = A->cols;
  int rows_b = B->rows;
  int cols_b = B->cols;

  int temp1;
  int temp2;

  matrix * final = newMatrix(rows_a*rows_b,cols_a*cols_b);
  for(int i = 1; i <= rows_a; i++){
    for(int j = 1; j <= cols_a; j++){
      temp1 = ELEM(A, i, j);
      for(int k = 1; k <= rows_b; k++){
        for(int l = 1; l <= cols_b; l++){
          temp2 = ELEM(B,k,l);
          printf("%i\n",temp1*temp2 );
          setElement(final, (i-1)*rows_a + k, (j-1)*cols_a + l, temp1*temp2);
        }
      }
    }
  }
  printMatrix(final);
  return final;
}

/* Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.
 */
int deleteMatrix(matrix * mtx) {
  if (!mtx) return -1;
  // free mtx's data
  assert (mtx->data);
  free(mtx->data);
  // free mtx itself
  free(mtx);
  return 0;
}

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

/* Copies a matrix.  Returns NULL if mtx is NULL.
 */
matrix * copyMatrix(matrix * mtx) {
  if (!mtx) return NULL;

  // create a new matrix to hold the copy
  matrix * cp = newMatrix(mtx->rows, mtx->cols);

  // copy mtx's data to cp's data
  memcpy(cp->data, mtx->data,
         mtx->rows * mtx->cols * sizeof(int));

  return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(matrix * mtx, int row, int col, int val)
{
  if (!mtx) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;

  ELEM(mtx, row, col) = val;
  return 0;
}

/* Sets the reference val to the value of the (row, col)
 * element of mtx.  Returns 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx.
 */
int getElement(matrix * mtx, int row, int col,
               int * val) {
  if (!mtx || !val) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;

  *val = ELEM(mtx, row, col);
  return 0;
}

/* Sets the reference n to the number of rows of mtx.
 * Returns 0 if successful and -1 if mtx or n is NULL.
 */
int nRows(matrix * mtx, int * n) {
  if (!mtx || !n) return -1;
  *n = mtx->rows;
  return 0;
}

/* Sets the reference n to the number of columns of mtx.
 * Returns 0 if successful and -1 if mtx is NULL.
 */
int nCols(matrix * mtx, int * n) {
  if (!mtx || !n) return -1;
  *n = mtx->rows;
  return 0;
}

/* Prints the matrix to stdout.  Returns 0 if successful
 * and -1 if mtx is NULL.
 */
int printMatrix(matrix * mtx) {
  if (!mtx) return -1;

  int row, col;
  for (row = 1; row <= mtx->rows; row++) {
    for (col = 1; col <= mtx->cols; col++) {
      // Print the floating-point element with
      //  - either a - if negative or a space if positive
      //  - at least 3 spaces before the .
      //  - precision to the hundredths place
      printf("% 6.2i ", ELEM(mtx, row, col));
    }
    // separate rows by newlines
    printf("\n");
  }
  return 0;
}

/* Writes the transpose of matrix in into matrix out.
 * Returns 0 if successful, -1 if either in or out is NULL,
 * and -2 if the dimensions of in and out are incompatible.
 */
int transpose(matrix * in, matrix * out) {
  if (!in || !out) return -1;
  if (in->rows != out->cols || in->cols != out->rows)
    return -2;

  int row, col;
  for (row = 1; row <= in->rows; row++)
    for (col = 1; col <= in->cols; col++)
      ELEM(out, col, row) = ELEM(in, row, col);
  return 0;
}

/* Writes the sum of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int sum(matrix * mtx1, matrix * mtx2, matrix * sum) {
  if (!mtx1 || !mtx2 || !sum) return -1;
  if (mtx1->rows != mtx2->rows ||
      mtx1->rows != sum->rows ||
      mtx1->cols != mtx2->cols ||
      mtx1->cols != sum->cols)
    return -2;

  int row, col;
  for (col = 1; col <= mtx1->cols; col++)
    for (row = 1; row <= mtx1->rows; row++)
      ELEM(sum, row, col) =
        ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
  return 0;
}

/* Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the
 * matrices are NULL, and -2 if the dimensions of the
 * matrices are incompatible.
 */
int product(matrix * mtx1, matrix * mtx2, matrix * prod) {
  if (!mtx1 || !mtx2 || !prod) return -1;
  if (mtx1->cols != mtx2->rows ||
      mtx1->rows != prod->rows ||
      mtx2->cols != prod->cols)
    return -2;

  int row, col, k;
  for (col = 1; col <= mtx2->cols; col++)
    for (row = 1; row <= mtx1->rows; row++) {
      int val = 0;
      for (k = 1; k <= mtx1->cols; k++)
        val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
      ELEM(prod, row, col) = val;
    }
  return 0;
}

/* Writes the dot product of vectors v1 and v2 into
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a
 * vector, and -3 if the vectors are of incompatible
 * dimensions.
 */
int dotProduct(matrix * v1, matrix * v2, int * prod) {
  if (!v1 || !v2 || !prod) return -1;
  if (v1->cols != 1 || v2->cols != 1) return -2;
  if (v1->rows != v2->rows) return -3;

  *prod = 0;
  int i;
  for (i = 1; i <= v1->rows; i++)
    *prod += ELEM(v1, i, 1) * ELEM(v2, i, 1);
  return 0;
}

int identity(matrix * m) {
  if (!m || m->rows != m->cols) return -1;
  int row, col;
  for (col = 1; col <= m->cols; col++)
    for (row = 1; row <= m->rows; row++)
      if (row == col)
        ELEM(m, row, col) = 1.0;
      else
        ELEM(m, row, col) = 0.0;
  return 0;
}

int isSquare(matrix * mtx) {
  return mtx && mtx->rows == mtx->cols;
}

int isDiagonal(matrix * mtx) {
  if (!isSquare(mtx)) return 0;
  int row, col;
  for (col = 1; col <= mtx->cols; col++)
    for (row = 1; row <= mtx->rows; row++)
      // if the element is not on the diagonal and not 0
      if (row != col && ELEM(mtx, row, col) != 0.0)
        // then the matrix is not diagonal
        return 0;
  return 1;
}

int isUpperTriangular(matrix * mtx) {
  if (!isSquare(mtx)) return 0;
  int row, col;
  // looks at positions below the diagonal
  for (col = 1; col <= mtx->cols; col++)
    for (row = col+1; row <= mtx->rows; row++)
      if (ELEM(mtx, row, col) != 0.0)
        return 0;
  return 1;
}

int diagonal(matrix * v, matrix * mtx) {
  if (!v || !mtx ||
      v->cols > 1 || v->rows != mtx->rows ||
      mtx->cols != mtx->rows)
    return -1;
  int row, col;
  for (col = 1; col <= mtx->cols; col++)
    for (row = 1; row <= mtx->rows; row++)
      if (row == col)
        ELEM(mtx, row, col) = ELEM(v, col, 1);
      else
        ELEM(mtx, row, col) = 0.0;
  return 0;
}




node* create(int data,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

/*
    add a new node at the beginning of the list
*/
node* prepend(node* head,int data)
{
    node* new_node = create(data,head);
    head = new_node;
    return head;
}

/*
    add a new node at the end of the list
*/
node* append(node* head, int data)
{
    if(head == NULL)
        return create(data,NULL);
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(data,NULL);
    cursor->next = new_node;

    return head;
}

/*
    insert a new node after the prev node
*/
node* insert_after(node *head, int data, node* prev)
{
    if(head == NULL || prev == NULL)
        return NULL;
    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != prev)
        cursor = cursor->next;

    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}

/*
    insert a new node before the nxt node
*/
node* insert_before(node *head, int data, node* nxt)
{
    if(nxt == NULL || head == NULL)
        return NULL;

    if(head == nxt)
    {
        head = prepend(head,data);
        return head;
    }

    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nxt)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}

/*
    traverse the linked list
*/
void traverse(node* head,callback f)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}
/*
    remove node from the front of list
*/
node* remove_front(node* head)
{
    if(head == NULL)
        return NULL;
    node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}

/*
    remove node from the back of the list
*/
node* remove_back(node* head)
{
    if(head == NULL)
        return NULL;

    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }

    if(back != NULL)
        back->next = NULL;

    /* if this is the last node in the list*/
    if(cursor == head)
        head = NULL;

    free(cursor);

    return head;
}

/*
    remove a node from the list
*/
node* remove_any(node* head,node* nd)
{
    if(nd == NULL)
        return NULL;
    /* if the node is the first node */
    if(nd == head)
        return remove_front(head);

    /* if the node is the last node */
    if(nd->next == NULL)
        return remove_back(head);

    /* if the node is in the middle */
    node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;

}
/*
    display a node
*/
void display(node* n)
{
    if(n != NULL)
        printf("%d ", n->data);
}

/*
    Search for a specific node with input data

    return the first matched node that stores the input data,
    otherwise return NULL
*/
node* search(node* head,int data)
{

    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->data == data)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

int searchInd(node* head,int data)
{

    node *cursor = head;
    int count = 1;
    while(cursor!=NULL)
    {
        if(cursor->data == data)
            return count;
        cursor = cursor->next;
        count++;
    }
    return 0;
}

/*
    remove all element of the list
*/
void dispose(node *head)
{
    node *cursor, *tmp;

    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}
/*
    return the number of elements in the list
*/
int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}
/*
    sort the linked list using insertion sort
*/
node* insertion_sort(node* head)
{
    node *x, *y, *e;

    x = head;
    head = NULL;

    while(x != NULL)
    {
        e = x;
        x = x->next;
        if (head != NULL)
        {
            if(e->data > head->data)
            {
                y = head;
                while ((y->next != NULL) && (e->data> y->next->data))
                {
                    y = y->next;
                }
                e->next = y->next;
                y->next = e;
            }
            else
            {
                e->next = head;
                head = e ;
            }
        }
        else
        {
            e->next = NULL;
            head = e ;
        }
    }
    return head;
}

/*
    reverse the linked list
*/
node* reverse(node* head)
{
    node* prev    = NULL;
    node* current = head;
    node* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}


int getLinkedElement(node * head, int element){
  node * temp = head;
  for(int i = 1; i < element; i++){
    if(temp->next){
      temp = temp->next;
    }
  }
  return temp->data;
}
/*
    display the menu
*/
void menu()
{
    printf("--- C Linked List Demonstration --- \n\n");
    printf("0.menu\n");
    printf("1.prepend an element\n");
    printf("2.append an element\n");
    printf("3.search for an element\n");
    printf("4.insert after an element\n");
    printf("5.insert before an element\n");
    printf("6.remove front node\n");
    printf("7.remove back node\n");
    printf("8.remove any node\n");
    printf("9.sort the list\n");
    printf("10.Reverse the linked list\n");
    printf("-1.quit\n");

}






node ** create_buchi(node ** trans) {
  int N_ap = 6;
  char * alphabet[N_ap];
  char * power_set[(int)(pow(2,N_ap))];
  getAlpha(alphabet, N_ap);
  getPowerSet(power_set,alphabet,N_ap);

  FILE *stream;

  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int alpha_len = 6;
  int sn_count = getStateNames(stream, BUCH_AUT, STATE_NAMES);

  //-----------------------------------------------------


  FILE *stream2;
  char *line2 = NULL;
  size_t len2 = 0;
  size_t read2;

  stream2 = fopen("LTLOUTPUT.txt", "r");

  if (stream2 == NULL)
    exit(EXIT_FAILURE);
  int begin2 = 0;

  int sn_count2 = -1;
  int end_trans = 0;
  char *token;

  callback disp = display;
  trans = (node**)malloc(sn_count*sn_count*sizeof(node * ));
  for(int i = 0; i < sn_count*sn_count; i++){
    trans[i] = NULL;
  }
  int trans_entry;
  node * curr_trans;
  int count = 0;

  //----------------------------------------------------------
  while ((read2 = getline(&line2, &len2, stream2)) != -1) {
    if(strstr(line2,"Buchi automaton after simplification")!= NULL & line2[0] == 'B'){
      begin2 = 1;
    }

    if(begin2 == 1 & strstr(line2, "never {")!= NULL){
      begin2 = 0;
    }
    if(begin2 == 1){
      if(strstr(line2, "state")){
        sn_count2++;
      }
      else if(sn_count2 >= 0){
        printf("%s%i\n",line2 ,sn_count2+1);
        char * end_state = strstr(line2, "->");
        if(end_state){
          printf("%s",end_state+3);
          for(int i = 0; i < sn_count; i++){
            if(strstr(end_state+3,STATE_NAMES[i])){
              end_trans = i;
              printf("%i\n",i);
            }
          }
          printf("%s\n","av" );

          count = 0;
          printf("%i\n",sn_count2 * sn_count +  end_trans - 1);
          trans_entry = sn_count2 * sn_count +  end_trans ;
          curr_trans = trans[trans_entry];
          printf("%s\n","av" );
          token = strtok(line2, " & ");
          while( token != NULL )
          {
            token[2] = '\0';
            if(token[0] == 'p'){
              if(count == 0 & trans[trans_entry] == NULL){
                for(int i = 0; i < (int)pow(2,N_ap); i++){
                  if(strstr(power_set[i], token)){
                      if(search(trans[trans_entry],i) == NULL) {
                        trans[trans_entry] = prepend(trans[trans_entry],i);
                      }

                        traverse(trans[trans_entry],disp);

                      printf("\n");
                    }
                  }
                  count++;
                }

                else if(count != 0){
                  printf("%s\n","MADE" );
                  reduce_list(trans[trans_entry],power_set,token);
                  printf("%s\n","MADE" );

                  count++;
                  printf("%c\n", 'd');
                }
                else if (trans){
                  for(int i = 0; i < (int)pow(2,N_ap); i++){
                    if(strstr(power_set[i], token)){
                        if(search(trans[trans_entry],i) == NULL) {
                          trans[trans_entry] = prepend(trans[trans_entry],i);
                        }

                          traverse(trans[trans_entry],disp);

                        printf("\n");
                      }
                    }
                }

              }
              traverse(trans[trans_entry],disp);
              printf("%s\n", token);

            if(token[0] == '!' & token[1] == 'p'){
              printf("Not a P");
            }
            else if(line2[0] != 'p' & line2[0] != '!'){
              for(int i = 0; i < pow(2,N_ap); i++){
                if(search(trans[trans_entry],i+1) == NULL){
                  trans[trans_entry] = prepend(trans[trans_entry],i+1);
                }
              }
            }
            token = strtok(NULL, " & ");
          }
        }
      }
    }
  }

  for(int i = 0; i < 13; i++){
    printf("%s %i\n",STATE_NAMES[i], i+1);
  }


  for(int i = 0; i < 30; i++){
    printf("\n");
  }

  for(int i = 0; i < sn_count; i++){
    for(int j = 0; j < sn_count; j++){
      if(trans[i*sn_count + j]){
        printf("%i,%i   :    ",i+1,j+1);
        trans[i*sn_count + j] = insertion_sort(trans[i*sn_count + j]);
        //traverse(trans[i*sn_count + j],disp);
        printf("\n\n\n");
      }

    }

  }
  for(int i = 0; i < sn_count; i++){
    for(int j = 0; j < sn_count; j++){
      if(trans[i*sn_count + j]){
        printf("%i,%i   :    ",i+1,j+1);
        //trans[i*sn_count + j] = insertion_sort(trans[i*sn_count + j]);
        traverse(trans[i*sn_count + j],disp);
        printf("\n\n\n");
      }

    }

  }
  return trans;
}







void getAlpha(char ** alpha, int N_ap) {
  for(int i = 0; i < N_ap; i++){
    alpha[i] = (char *)malloc((i/10)*sizeof(char));
    sprintf(alpha[i], "p%d", i+1);
  }
}

void getPowerSet(char ** power_set, char ** alpha, int N_ap){
  char temp[N_ap];
  for(int i = 0; i < pow(2,N_ap); i++){
    dec2bin(temp, i, N_ap-1);
    power_set[i] = (char *)malloc(20 * sizeof(char));
    for(int j = 0; j < N_ap; j++){
      if(temp[N_ap-j-1] == '1'){
        strncpy(&power_set[i][strlen(power_set[i])], alpha[j],2);
      }
    }
  }
}

void dec2bin(char* arry, int dec, int length){
   int i = 0;
   for(i = length; i >= 0; i--){
     if((dec & (1 << i)) != 0){
       sprintf(&arry[length-i], "%d", 1);
     }else{
       sprintf(&arry[length-i], "%d", 0);
     }
   }
}

int unique(int * array, int num, int count){
  if(array == NULL){return 1;}
  int uniq = 1;
  for(int i = 0; i <= count; i++){
    if(array[i] == num){
      return 0;
    }
  }
  return uniq;
}








Buchi * Buchi_Struct() {
  Buchi * B1 = (Buchi * )malloc(sizeof(Buchi));
  int N_ap = 7;
  char * alphabet[N_ap];
  char * power_set[(int)(pow(2,N_ap))];
  getAlpha(alphabet, N_ap);
  getPowerSet(power_set,alphabet,N_ap);

  FILE *stream;

  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int alpha_len = 7;
  int sn_count = getStateNames(stream, BUCH_AUT, STATE_NAMES);

  //-----------------------------------------------------


  FILE *stream2;
  char *line2 = NULL;
  size_t len2 = 0;
  size_t read2;

  stream2 = fopen("LTLOUTPUT.txt", "r");

  if (stream2 == NULL)
    exit(EXIT_FAILURE);
  int begin2 = 0;

  int sn_count2 = -1;
  int end_trans = 0;
  char *token;

  callback disp = display;

  B1->Trans = newCellMatrix(sn_count,sn_count);
  node ** trans = B1->Trans->data;
  B1->F = NULL;
  B1->S0 = NULL;
  B1->S = NULL;
  for(int i = 1; i <= sn_count; i++){
    B1->S = append(B1->S, i);
  }

  int trans_entry;
  node * curr_trans;
  int count = 0;

  //----------------------------------------------------------
  while ((read2 = getline(&line2, &len2, stream2)) != -1) {
    if(strstr(line2,"Buchi automaton after simplification")!= NULL & line2[0] == 'B'){
      begin2 = 1;
    }

    if(begin2 == 1 & strstr(line2, "never {")!= NULL){
      begin2 = 0;
    }
    if(begin2 == 1){
      if(strstr(line2, "state")){
        if(strstr(line2, "init")){
          if(sn_count2 == -1){
            B1->S0 = append(B1->S0, 1);
          }
          else{
            B1->S0 = append(B1->S0, sn_count2);
          }

        }
        if(strstr(line2, "accept")){
          B1->F = append(B1->F, sn_count2+2);
        }
        sn_count2++;
      }
      else if(sn_count2 >= 0){
        printf("%s%i\n",line2 ,sn_count2+1);
        char * end_state = strstr(line2, "->");
        if(end_state){
          printf("%s",end_state+3);
          for(int i = 0; i < sn_count; i++){
            if(strstr(end_state+3,STATE_NAMES[i])){
              end_trans = i;
              printf("%i\n",i);
            }
          }
          printf("%s\n","av" );

          count = 0;
          printf("%i\n",sn_count2 * sn_count +  end_trans - 1);
          trans_entry = sn_count2 * sn_count +  end_trans ;
          curr_trans = trans[trans_entry];
          printf("%s\n","av" );
          token = strtok(line2, " & ");
          while( token != NULL )
          {
            token[2] = '\0';
            if(token[0] == 'p'){
              if(count == 0 & trans[trans_entry] == NULL){
                for(int i = 0; i < (int)pow(2,N_ap); i++){
                  if(strstr(power_set[i], token)){
                      if(search(trans[trans_entry],i) == NULL) {
                        trans[trans_entry] = prepend(trans[trans_entry],i);
                      }

                        traverse(trans[trans_entry],disp);

                      printf("\n");
                    }
                  }
                  count++;
                }

                else if(count != 0){
                  printf("%s\n","MADE" );
                  reduce_list(trans[trans_entry],power_set,token);
                  printf("%s\n","MADE" );

                  count++;
                  printf("%c\n", 'd');
                }
                else if (trans){
                  for(int i = 0; i < (int)pow(2,N_ap); i++){
                    if(strstr(power_set[i], token)){
                        if(search(trans[trans_entry],i) == NULL) {
                          trans[trans_entry] = prepend(trans[trans_entry],i);
                        }

                          traverse(trans[trans_entry],disp);

                        printf("\n");
                      }
                    }
                }

              }
              traverse(trans[trans_entry],disp);
              printf("%s\n", token);

            if(token[0] == '!' & token[1] == 'p'){
              printf("Not a P");
            }
            else if(line2[0] != 'p' & line2[0] != '!'){
              for(int i = 0; i < pow(2,N_ap); i++){
                if(search(trans[trans_entry],i+1) == NULL){
                  trans[trans_entry] = prepend(trans[trans_entry],i+1);
                }
              }
            }
            token = strtok(NULL, " & ");
          }
        }
      }
    }
  }

  for(int i = 0; i < 13; i++){
    printf("%s %i\n",STATE_NAMES[i], i+1);
  }


  for(int i = 0; i < 30; i++){
    printf("\n");
  }

  for(int i = 0; i < sn_count; i++){
    for(int j = 0; j < sn_count; j++){
      if(trans[i*sn_count + j]){
        printf("%i,%i   :    ",i+1,j+1);
        trans[i*sn_count + j] = insertion_sort(trans[i*sn_count + j]);
        //traverse(trans[i*sn_count + j],disp);
        printf("\n\n\n");
      }

    }

  }
  for(int i = 0; i < sn_count; i++){
    for(int j = 0; j < sn_count; j++){
      if(trans[i*sn_count + j]){
        printf("%i,%i   :    ",i+1,j+1);
        //trans[i*sn_count + j] = insertion_sort(trans[i*sn_count + j]);
        traverse(trans[i*sn_count + j],disp);
        printf("\n\n\n");
      }

    }

  }
  B1->Trans->data = trans;
  return B1;
}




void reduce_list(node * head, char ** power_set, char * token){
  node* cursor = head;
  node * temp;
  while(cursor != NULL)
  {
    if(strstr(power_set[cursor->data], token) == NULL){
      temp = cursor;
      cursor = remove_any(head,temp);
    }
      cursor = cursor->next;
  }
}




int getStateNames(FILE * stream, char * BUCH_AUT, char ** STATE_NAMES){

  char *line = NULL;
  size_t len = 0;
  size_t read;
  stream = fopen("LTLOUTPUT.txt", "r");

  if (stream == NULL)
    exit(EXIT_FAILURE);
  int begin = 0;

  //Read in the buchi automation after simplification and State names
  int prev_len = 0;
  int sn_count = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    if(strstr(line,"Buchi automaton after simplification")!= NULL & line[0] == 'B'){
      begin = 1;
    }

    if(begin == 1 & strstr(line, "never {")!= NULL){
      begin = 0;
    }
    if(begin == 1){

      //printf("%s", strstr(line,"state"));
      strncpy(&BUCH_AUT[prev_len], line, read);
      prev_len += read;
      if(strstr(line, "state")!=NULL){
        STATE_NAMES[sn_count] = (char *)malloc(read*sizeof(char));
        strncpy(STATE_NAMES[sn_count], &line[6],read-6);
        //printf("%s\n", STATE_NAMES[sn_count]);
        sn_count++;
      }
    }
  }
  free(line);
  fclose(stream);
  return sn_count;
}
