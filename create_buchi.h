


typedef struct {
  int rows;
  int cols;
  int * data;
} matrix;

typedef struct node
{
    int data;
    struct node* next;
} node;




matrix * newMatrix(int rows, int cols);
matrix * kronProd(matrix * A, matrix * B);
int deleteMatrix(matrix * mtx);

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

matrix * copyMatrix(matrix * mtx);
int setElement(matrix * mtx, int row, int col, int val);
int getElement(matrix * mtx, int row, int col,
               int * val);
int nRows(matrix * mtx, int * n);
int nCols(matrix * mtx, int * n);
int printMatrix(matrix * mtx);
int transpose(matrix * in, matrix * out);
int sum(matrix * mtx1, matrix * mtx2, matrix * sum);
int product(matrix * mtx1, matrix * mtx2, matrix * prod);
int dotProduct(matrix * v1, matrix * v2, int * prod);

int identity(matrix * m);

int isDiagonal(matrix * mtx);

int isUpperTriangular(matrix * mtx);

int diagonal(matrix * v, matrix * mtx);


/*
    Linked list
*/

typedef void (*callback)(node* data);

/*
    create a new node
    initialize the data and next field

    return the newly created node
*/
node* create(int data,node* next);

/*
    add a new node at the beginning of the list
*/
node* prepend(node* head,int data);


/*
    add a new node at the end of the list
*/
node* append(node* head, int data);

/*
    insert a new node after the prev node
*/
node* insert_after(node *head, int data, node* prev);

/*
    insert a new node before the nxt node
*/
node* insert_before(node *head, int data, node* nxt);

/*
    traverse the linked list
*/
void traverse(node* head,callback f);
/*
    remove node from the front of list
*/
node* remove_front(node* head);

/*
    remove node from the back of the list
*/
node* remove_back(node* head);
/*
    remove a node from the list
*/
node* remove_any(node* head,node* nd);
/*
    display a node
*/
void display(node* n);

/*
    Search for a specific node with input data

    return the first matched node that stores the input data,
    otherwise return NULL
*/
node* search(node* head,int data);
int searchInd(node* head,int data);

/*
    remove all element of the list
*/
void dispose(node *head);
/*
    return the number of elements in the list
*/
int count(node *head);
/*
    sort the linked list using insertion sort
*/
node* insertion_sort(node* head);

node* reverse(node* head);
/*
    display the menu
*/
void menu();



void dec2bin(char* arry, int dec, int length);
void getAlpha(char ** alpha, int N_ap);
void getPowerSet(char ** power_set, char ** alpha, int N_ap);
int getStateNames(FILE * stream, char * BUCH_AUT, char ** STATE_NAMES);
int unique(int * array, int num, int count);
void reduce_list(node * head, char ** power_set, char * token);
node ** create_buchi(node ** trans);
