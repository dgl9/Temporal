#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "library.h"
#include <time.h>


int main() {
  /* code */
  srand(time(NULL));
  int T1[] = {1, 1,1,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,1,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1};


  matrix * Tadj = newMatrix(9,9);
  for(int i = 0; i < 9;i++){
    for(int j = 0; j < 9; j++){
      ELEM(Tadj,i+1,j+1) = T1[i*9 + j];
    }
  }
  printMatrix(Tadj);
  int TQ1[] = {1,2,3,4,5,6,7,8,9};
  int Tx1[] = {0, 0, 4, 6, 8, 8, 8, 4, 10};
  int Ty1[] = {0, 4, 4, 4, 4, 2, 0, 0, 2};

  node * TQ = NULL;
  node * Tx = NULL;
  node * Ty = NULL;

  callback disp = display;

  TQ = AppendList(TQ,TQ1,9);
  Tx = AppendList(Tx, Tx1, 9);
  Ty = AppendList(Ty, Ty1, 9);
  traverse(TQ,disp);
  printf("\n");
  traverse(Tx,disp);
  printf("\n");
  traverse(Ty,disp);

  int maxNum= 9;
  int BigNum = 1000000;

  matrix * dist = DistanceMatrix(Tadj, Tx, Ty, BigNum);
  printMatrix(dist);

  int N=9;
  int x01[] = {1,2,3,4,5,6,7,8,1};
  node * x0 = AppendList(x0,x01,9);

  int d=2*N;


  //--------Buchi Automaton--------
  int N_p = 7;
  Buchi * B1;
  FILE *stream;
  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int sn_count = getStateNamesNew(stream, BUCH_AUT, STATE_NAMES);
  B1 = Buchi_Struct_New();
  printf("\n\n\n\n");
  printCellMatrix(B1->Trans);
  printf("\n\n\n\n");
  traverse(B1->S0,disp);
  printf("\n\n\n\n");
  traverse(B1->S,disp);
  printf("\n\n\n\n");
  traverse(B1->F,disp);



    //--------end of Buchi automation--------



  //-------------Atomic Propositions--------
  cell_matrix * AP = newCellMatrix(N_p,N+2);
  int num = -100;

  //AP(:,:)={num}; initialize all of the cells to a number
  for(int i = 1; i <= N_p;i++ ){
    SetCell(AP,i,N+1,pow(2,i-1));
  }


  SetCell(AP,1,1,5);
  SetCell(AP,1,2,5);
  SetCell(AP,1,3,5);

  SetCell(AP,2,2,1);
  SetCell(AP,2,3,1);
  SetCell(AP,2,4,1);

  SetCell(AP,3,4,7);
  SetCell(AP,3,5,7);
  SetCell(AP,3,6,7);

  SetCell(AP,4,6,8);
  SetCell(AP,4,7,8);

  SetCell(AP,5,7,4);
  SetCell(AP,5,8,4);

  SetCell(AP,6,8,3);
  SetCell(AP,6,9,3);

  SetCell(AP,7,1,7);

  for(int i = 1; i <=  AP->rows; i++){
    for(int j = 1; j <= AP->cols - 2; j++){
      if(getCell(AP,i,j)!=NULL){
        AppendToCell(AP,i,N+2,j);
      }
      else{
        SetCell(AP,i,j,num);
      }
    }
  }
  printCellMatrix(AP);

   //AP(7,N+2)={6};AP(8,N+2)={2};%AP(8,N+2)={[6,7]};%indices of rbts involved in satisfaction of an AP
  //-------------------------------------
  int nMaxPre=1000;
  int n = ListLength(B1->S)*(maxNum)*N;
  matrix * parent=newMatrix(nMaxPre,1);
  matrix * Qpba = newMatrix(nMaxPre,N+1);
  //initializing Qpba

  node * temp = x0;
  for(int i = 1; i <= ListLength(x0); i++){
    setElement(Qpba,1,i,temp->data);
    temp = temp->next;
  }
  setElement(Qpba,1,Qpba->cols,B1->S0->data);
  printMatrix(Qpba);

  node * path;
  float epsilon=0.1;
  int ind = 2;
  int stop=0;
  matrix * CostNode= newMatrix(nMaxPre,1);
  matrix * SizeTree= newMatrix(nMaxPre,1);
  //==================Build Prefix part========================================
  int goal = B1->F->data;
  node * F;
  matrix * reject = newMatrix(1,nMaxPre);
  int sample=0;
  matrix * rejectExist= newMatrix(1,nMaxPre);
  matrix * rejectInf= newMatrix(1,nMaxPre);
  int f = 1;

  int qBPrev;

  for(int n = 1; n <= nMaxPre-1; n++){
    node * xNew = sampleReachablePTSpointTree(Qpba, N, Tadj, Tx, Ty,TQ,ind); //FIGURE THESE OUT TOMORROW
    node * sat = observeInDiscreteEnvironment(N,N_p,AP,xNew,epsilon);
    traverse(sat,disp);
    setElement(reject,1,n,0);

    for(int q2 = 1; q2 <= ListLength(B1->S); q2++){
      qBPrev = getLinkedElement(B1->S, q2);
      printf("\n%i\n", qBPrev);

    }
  }



  return 0;

}
