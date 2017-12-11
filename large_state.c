#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "library.h"
#include <time.h>
#include <unistd.h>



int main() {
  /* code */
  srand(time(NULL));
  matrix * Tadj = getAdj(9);







  printMatrix(Tadj);

  int TQ1[] = {1,2,3,4,5,6,7,8,9};
  int Tx1[] = {0,  0,  4,  6,  8,  8,  8,  4, 10};
  int Ty1[] = {0, 4, 4, 4, 4, 2,      0,      0, 2};

  node * TQ = NULL;
  node * Tx = NULL;
  node * Ty = NULL;

  callback disp = display;

  TQ = AppendList(TQ,TQ1,9);
  Tx = AppendList(Tx, Tx1, 9);
  Ty = AppendList(Ty, Ty1, 9);
  //traverse(TQ,disp);
  //printf("\n");
  //traverse(Tx,disp);
  //printf("\n");
  //traverse(Ty,disp);

  int maxNum= 9;
  int BigNum = 1000000;

  matrix * dist = DistanceMatrix(Tadj, Tx, Ty, BigNum);
  printMatrix(dist);

  int N=9;
  int x01[] = {5,5,3,7,7,7,7,4,1};
  node * x0 = AppendList(x0,x01,9);

  int d=2*N;


  //--------Buchi Automaton--------
  int N_p = 6;
  Buchi * B1;
  FILE *stream;
  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int sn_count = getStateNamesNew(stream, BUCH_AUT, STATE_NAMES);
  getchar();
  B1 = Buchi_Struct_New(6);

  matrix * neig = newMatrix(sn_count,sn_count);


  for(int j1 = 1; j1 <= sn_count; j1++){
    for(int j2 = 1; j2 <= sn_count; j2++){
      if(CELL(B1->Trans,j1,j2)){
        setElement(neig,j1,j2,1);
      }
    }
  }


  //printf("\n\n\n\n");
  //printCellMatrix(B1->Trans);
  //printf("\n\n\n\n");
  //traverse(B1->S0,disp);
  //printf("\n\n\n\n");
  //traverse(B1->S,disp);
  //printf("\n\n\n\n");
  //traverse(B1->F,disp);
    //printMatrix(neig);



    //--------end of Buchi automation--------

  //
  //
  // //-------------Atomic Propositions--------
  cell_matrix * AP = newCellMatrix(N_p,N+2);
  int num = -100;

  //AP(:,:)={num}; initialize all of the cells to a number
  for(int i = 1; i <= N_p;i++ ){
    SetCell(AP,i,N+1,pow(2,i-1));
  }

  SetCell(AP,1,1,5);
  SetCell(AP,1,2,5);


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



  for(int i = 1; i <=  AP->rows ; i++){
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
  //
  //  //AP(7,N+2)={6};AP(8,N+2)={2};%AP(8,N+2)={[6,7]};%indices of rbts involved in satisfaction of an AP
  // //-------------------------------------



  int nMaxPre=8000;
  int n = ListLength(B1->S)*(maxNum)*N;
  matrix * parent=newMatrix(nMaxPre*10,1);
  matrix * Qpba = newMatrix(nMaxPre*10,N+1);
  //initializing Qpba

  node * temp = x0;
  for(int i = 1; i <= ListLength(x0); i++){
    setElement(Qpba,1,i,temp->data);
    temp = temp->next;
  }

  setElement(Qpba,1,Qpba->cols,2);// B1->S0->data);

  //printMatrix(Qpba);

  node * path;
  float epsilon=0;
  int ind = 2;
  int stop=0;
  matrix * CostNode= newMatrix(nMaxPre*10,1);
  matrix * SizeTree= newMatrix(nMaxPre*10,1);
  printCellMatrix(B1->Trans);
  printMatrix(neig);

  //==================Build Prefix part========================================
  int goal = B1->F->data;
  node * F = NULL;
  matrix * reject = newMatrix(1,nMaxPre*10);
  int sample=0;
  matrix * rejectExist= newMatrix(1,nMaxPre*10);
  matrix * rejectInf= newMatrix(1,nMaxPre*10);
  int f = 1;
  node * candParents = NULL;
  node * xNew = NULL;
  node * sat = NULL;
  node * indices = NULL;
  node * qPrev;

  matrix * QNext;

  int qBnext;
  int qBPrev;
  matrix * QPTS;
  matrix * QB;
  int prevQPBAindex;
  int newCost;
  int par;

  getchar();
  // FILE * stream8 = fopen("sample_locs.txt", "r");
  // node * blah =  get_location(stream8, 9);
  // traverse(blah,disp);
  getchar();
    //getchar();

  //   getchar();
  //   node * samplePos = NULL;
  //   samplePos = append(samplePos,5);
  //   samplePos = append(samplePos,5);
  //   samplePos = append(samplePos,1);
  //   samplePos = append(samplePos,7);
  //   samplePos = append(samplePos,7);
  //   samplePos = append(samplePos,7);
  //   samplePos = append(samplePos,1);
  //   samplePos = append(samplePos,3);
  //   samplePos = append(samplePos,3);
  //   getchar();
  //
  //
  //
  // sat = observeInDiscreteEnvironment(N,N_p,AP,samplePos,0);
  // traverse(sat,disp);
  FILE * stream8 = fopen("sample_locs.txt", "r");

  for(int n = 1; n <= nMaxPre; n++){

    if(!(n%50)){
      printf("n : %i\n", n);
    }
    dispose(xNew);
    xNew = NULL;
    dispose(sat);
    sat = NULL;

    node * xNew =  sampleReachablePTSpointTree(Qpba, N, Tadj, Tx, Ty,TQ,ind); //FIGURE THESE OUT TOMORROW
    // getchar();
    // get_location(stream8, 9);
    // traverse(xNew,disp);

    sat = observeInDiscreteEnvironment(N,N_p,AP,xNew,0);



    ////printf("SAT\n");
    //traverse(xNew,disp);
    setElement(reject,1,n,0);

    for(int q2 = 1; q2 <= ListLength(B1->S); q2++){


      qBnext = getLinkedElement(B1->S, q2);
      //printf("\nQQQNEE%i\n", qBnext);
      dispose(candParents);
      candParents = NULL;

      candParents = findBuchiNeighbors(qBnext,neig);


        //printf("\n1wwwerqw%i\n", qBnext);
      //traverse(candParents,disp);
      //printf("\n1wwwerqw%i\n", qBnext);
      dispose(indices);
      indices = NULL;
      if(candParents){
        for(int jj = 1; jj <= ListLength(candParents); jj++){
          //printf("\n1wwwerqw%i\n", qBnext);
          qBPrev = getLinkedElement(candParents,jj);

          for(int i = 1; i <= ind; i++){
            if(qBPrev == ELEM(Qpba,i,N+1)){
              indices = append(indices,i);
            }
          }

        }
      }

      if(indices){
        //printf("DAVID\n");
        //traverse(indices,disp);
        //printf("DAVID\n");
        deleteMatrix(QPTS);
        QPTS = NULL;
        deleteMatrix(QB);
        QB = NULL;
        dispose(qPrev);
        qPrev = NULL;

        QPTS = Qpts(Qpba,indices,N);

        QB = Qb(Qpba,indices,N);
        //printMatrix(QPTS);
        //printMatrix(QB);
        prevQPBAindex = findPrevPTSpoint(QPTS,xNew,dist,BigNum,CostNode,indices);
        //printMatrix(QPTS);
        //printf("prevQPBAindex%i\n", prevQPBAindex);
        if(prevQPBAindex){

          qPrev = BuildQPREV(QPTS,QB,prevQPBAindex);
          //printf("QPREV\n");
          //traverse(qPrev,disp);
          //printf("QPRV\n");
          deleteMatrix(QNext);
          QNext = BuildQNEXT(xNew,qBnext,N);
          //printf("QNEXT\n");
          //printMatrix(QNext);
          //printf("QNEX\n");
          //printf("ismem\n");
          //printf("break\n");
          //printf("ismem\n");
          //printf("break\n");
          //printMatrix(Qpba);
          //printf("AMOUNT OF INDS\n%i", ind);
          //printf("AMOUNT OF INDS\n");
          if(!(ismemberRows(QNext,Qpba))){
            if(search(CELL(B1->Trans,getLinkedElement(qPrev,N+1),qBnext),LLSUM(sat))){
              //printf("gotit\n");
              for(int d = 1; d<= N+1; d++){
                ELEM(Qpba,ind,d) = ELEM(QNext,1,d);
              }
              ELEM(parent,ind,1) = ismemberRows(linkedToMatrix(qPrev),Qpba)->data;
              par = ELEM(parent,ind,1);
              //printf("parent%i\n",ELEM(parent,ind,1));

              ELEM(CostNode,ind,1) = ELEM(CostNode,par,1) + costTree(par,ind,dist,Qpba);
              //printf("parent%i\n",ELEM(parent,ind,1));
              //printf("Cost 1 %i\n",ELEM(dist,ELEM(Qpba,par,1),ELEM(Qpba,ind,1)) );
              //printf("Cost 2 %i\n",ELEM(dist,ELEM(Qpba,par,2),ELEM(Qpba,ind,2)) );
              //printf("costTree%i\n", costTree(par,ind,dist,Qpba));
              //printf("TOTAL%i\n", ELEM(CostNode,ind,1));
              if(ELEM(CostNode,ind,1) > BigNum){
                        ////getchar();
              }

              if((search(B1->F,qBnext) != NULL) | (qBnext == 3)){

                printf("GOAL\n");
                F = append(F,ind);
              }
              rewire(Qpba,parent,CostNode,Tadj,AP,B1->Trans,dist, ind, N_p, N);
              ind++;
            }
          }

          else{
            //printf("nogood\n");
          }
        }




      }
        // for jj=1:length(candParents)%for each possible qBprev
        //     qBPrev=candParents(jj);
        //     indices=[indices;find(Qpba(:,N+1)==qBPrev)];%indices of states in Qpba that point at states in Qba that reach the Buchi state qBnext
        // end
        // if ~isempty(indices)
        //     % Find the nearest node to xNew among all states in Qpba q=(?,qBprev):
        //     Qpts=Qpba(indices,1:N);
        //     Qb=Qpba(indices,N+1);
        //     %Given qNext=(xNew,qBnext), we have to determine: qPrev=(xPrev(?), qBPrev(?)):
        //     %[xPrev,indexQpts]=findPrevPTSpoint(Qpts,xNew,Dist,BigNum);%indexQpts points at the indexQpts-th state of subspace [Qpts,Qb]
        //     [xPrev,indexQpts]=findPrevPTSpoint_star_V2(Qpts,Qb,Qpba,xNew,qBnext,Dist,BigNum,parent,B1,AP,N_p,epsilon);
        //     qBPrev=Qb(indexQpts); %goal
        //     qPrev=[xPrev,qBPrev];%parent %goal

    }

  }
  // printMatrix(Qpba);
  // printMatrix(parent);
  // printMatrix(CostNode);
  // printMatrix(neig);
  // printMatrix(CostNode);
  //printCellMatrix(B1->Trans);
  xNew = NULL;
  xNew = append(xNew,1);
  xNew = append(xNew,1);
  xNew = append(xNew,1);
  xNew = append(xNew,1);
  xNew = append(xNew,3);
  xNew = append(xNew,7);
  xNew = append(xNew,6);
  xNew = append(xNew,7);
  xNew = append(xNew,2);

  //traverse(observeInDiscreteEnvironment(N,N_p,AP,xNew,epsilon),disp);


  subprintMatrix(Qpba,ind);
  //printMatrix(parent);
  //printf("\n");
  //printf("COST\n");
  //printMatrix(CostNode);
  if(F){
    //traverse(F,disp);
    int goalNode;
    int parentNode;
    for(int i = 1; i <= ListLength(F); i++){
      goalNode = getLinkedElement(F,i);
      parentNode = goalNode;
      //printf("COST : %i\n", ELEM(CostNode,parentNode,1));
      printf("PREFIX : %i\n", i);
      while(parentNode != 0){
        printMatrixLine(Qpba, parentNode);
        parentNode = ELEM(parent,parentNode,1);
      }
      //printf("\n");
  }
}
// printMatrix(Qpba);
printf("starting suffix\n");
//getchar();
  // BUILD SUFFIX --------------------------------------------------------
matrix * QpbaPre= copyMatrix(Qpba);
cell_matrix * FinalSuffix= newCellMatrix(ListLength(F),1);
matrix * CostSuffix=newMatrix( BigNum*(ListLength(F),1), 1);
reject= newMatrix(1,30000);
matrix * sizeTreeSuf= newMatrix(1,30000);

node * sat0 = NULL;
matrix * qPBA0 = newMatrix(1,Qpba->cols);
int qB;
int tempGoalInd;
x0 = NULL;
int nMaxSuf;
int stopTree;
node * pathSuf = NULL;
int indGoal;
node * FinalSuffs = NULL;


for(int f = 1; f <= ListLength(F); f++){

  printf("Prefix Connect Ind : %i\n",f);
  sample = 0;
  tempGoalInd = getLinkedElement(F,f);

  for(int i = 1; i <= N+1; i++){
    ELEM(qPBA0,1,i) = ELEM(QpbaPre,tempGoalInd,i);
  }

  qB = ELEM(QpbaPre,tempGoalInd, N+1);

  for(int i = 1; i <= N; i++){
    x0 = append(x0,ELEM(QpbaPre,tempGoalInd,i));
  }

  sat0 = observeInDiscreteEnvironment(N,N_p,AP,x0,epsilon);

//--------------------------------------------------------
  deleteMatrix(Qpba);
  Qpba = newMatrix(n*5, N+1);

  for(int i = 1; i <= N+1; i++){
    ELEM(Qpba,1, i) = ELEM(QpbaPre,tempGoalInd,i);
  }
  //printf("sat0 ");
  //traverse(sat0,disp);
  //traverse(x0, disp);
  //subprintMatrix(Qpba,1);
  //getchar();

  parent = newMatrix(n*5,1);
  dispose(pathSuf);
  pathSuf = NULL;
  epsilon = 0;
  ind = 2;
  stop = 0;
  CostNode = newMatrix(n*5,1);
  node * SaveInd = NULL;
  stopTree = 0;

  if ( search( CELL(B1->Trans,qB,qB), LLSUM(sat0) ) ) {
    SaveInd = append(SaveInd,1);
    stopTree = 1;
  }

  nMaxSuf = nMaxPre;
  if(!stopTree){
    for(int n = 1; n <= nMaxSuf - 3; n++){
      if(!(n%50)){
        printf("n : %i\n",n );
      }


      dispose(xNew);
      xNew = NULL;
      dispose(sat);
      sat = NULL;
      xNew = sampleReachablePTSpointTree(Qpba, N, Tadj, Tx, Ty,TQ,ind); //FIGURE THESE OUT TOMORROW
      sat = observeInDiscreteEnvironment(N,N_p,AP,xNew,epsilon);

      //printf("SAT\n");
      //traverse(xNew,disp);
      setElement(reject,1,n,0);

      for(int q2 = 1; q2 <= ListLength(B1->S); q2++){
        qBnext = getLinkedElement(B1->S, q2);
        //printf("\nQQQNEE%i\n", qBnext);
        dispose(candParents);
        candParents = NULL;
        candParents = findBuchiNeighbors(qBnext,neig);
          //printf("\n1wwwerqw%i\n", qBnext);
        //traverse(candParents,disp);
        //printf("\n1wwwerqw%i\n", qBnext);
        dispose(indices);
        indices = NULL;
        if(candParents){
          for(int jj = 1; jj <= ListLength(candParents); jj++){
            //printf("\n1wwwerqw%i\n", qBnext);
            qBPrev = getLinkedElement(candParents,jj);
            for(int i = 1; i <= ind; i++){
              if(qBPrev == ELEM(Qpba,i,N+1)){
                indices = append(indices,i);
              }
            }

          }
        }

        if(indices){
          //printf("DAVID\n");
          //traverse(indices,disp);
          //printf("DAVID\n");
          deleteMatrix(QPTS);
          QPTS = NULL;
          deleteMatrix(QB);
          QB = NULL;
          dispose(qPrev);
          qPrev = NULL;

          QPTS = Qpts(Qpba,indices,N);

          QB = Qb(Qpba,indices,N);
          //printMatrix(QPTS);
          //printMatrix(QB);
          prevQPBAindex = findPrevPTSpoint(QPTS,xNew,dist,BigNum,CostNode,indices);
          //printMatrix(QPTS);
          //printf("prevQPBAindex%i\n", prevQPBAindex);
          if(prevQPBAindex){

            qPrev = BuildQPREV(QPTS,QB,prevQPBAindex);
            //printf("QPREV\n");
            //traverse(qPrev,disp);
            //printf("QPRV\n");
            deleteMatrix(QNext);
            QNext = BuildQNEXT(xNew,qBnext,N);
            //printf("QNEXT\n");
            //printMatrix(QNext);
            //printf("QNEX\n");
            //printf("ismem\n");
            //printf("break\n");
            //printf("ismem\n");
            //printf("break\n");
            //printMatrix(Qpba);
            ////printf("AMOUNT OF INDS\n%i", ind);
            ////printf("AMOUNT OF INDS\n");
            if(!(ismemberRows(QNext,Qpba))){
              if(search(CELL(B1->Trans,getLinkedElement(qPrev,N+1),qBnext),LLSUM(sat))){
                //printf("gotit\n");
                for(int d = 1; d<= N+1; d++){
                  ELEM(Qpba,ind,d) = ELEM(QNext,1,d);
                }
                ELEM(parent,ind,1) = ismemberRows(linkedToMatrix(qPrev),Qpba)->data;
                par = ELEM(parent,ind,1);
                //printf("parent%i\n",ELEM(parent,ind,1));

                ELEM(CostNode,ind,1) = ELEM(CostNode,par,1) + costTree(par,ind,dist,Qpba);
                //printf("parent%i\n",ELEM(parent,ind,1));
                //printf("Cost 1 %i\n",ELEM(dist,ELEM(Qpba,par,1),ELEM(Qpba,ind,1)) );
                //printf("Cost 2 %i\n",ELEM(dist,ELEM(Qpba,par,2),ELEM(Qpba,ind,2)) );
                //printf("costTree%i\n", costTree(par,ind,dist,Qpba));
                //printf("TOTAL%i\n", ELEM(CostNode,ind,1));
                if(ELEM(CostNode,ind,1) > BigNum){
                          //getchar();
                }

                rewire(Qpba,parent,CostNode,Tadj,AP,B1->Trans,dist, ind, N_p, N);
                ind++;

                if(check_pts(Qpba, Tadj, ind-1, 1) & (search(CELL(B1->Trans,qBnext, qB), LLSUM(sat0)) != NULL) ){
                  printf("Loop Found at Ind : %i with cost : %i\n",ind-1, ELEM(CostNode,ind-1,1) );
                  stop = 1;
                  //getchar();
                  for(int d = 1; d<= N+1; d++){
                    ELEM(Qpba,ind,d) = ELEM(QpbaPre,tempGoalInd,d);
                  }
                  ELEM(parent,ind,1) = ind - 1;
                  indGoal = ind;



                  ind++;
                  SaveInd = append(SaveInd, ind-1);
                  //getchar();
                }


              }
            }

            else{
              //printf("nogood\n");
            }
          }


        }
      }
    }
  }
  if(!SaveInd){
    FinalSuffs = append(FinalSuffs,0);
  }
  else{


    int tempIndy = getLinkedElement(SaveInd,1);
    int min_indy = tempIndy;
    int temp_cost = ELEM(CostNode,tempIndy,1);
    for(int i = 2; i <= ListLength(SaveInd); i++){
      tempIndy = getLinkedElement(SaveInd,i);
      if(ELEM(CostNode,tempIndy,i) < temp_cost ){
        temp_cost = ELEM(CostNode,tempIndy,i);
        min_indy = tempIndy;
      }
    }
    // int preParentNode = tempGoalInd;
    // printf("PREFIX : %i\n", f );
    // while(preParentNode){
    //   printMatrixLine(QpbaPre, preParentNode);
    //   parentNode =
    // }

    int parentNode = min_indy;
    printf("SUFFIX : %i\n", f);
    while(parentNode != 0){
      printMatrixLine(Qpba, parentNode);
      parentNode = ELEM(parent,parentNode,1);
    }
    FinalSuffs = append(FinalSuffs,min_indy);
    //print Prefix
    //Print Suffix
  }
  traverse(SaveInd,disp);

}
traverse(F,disp);
printf("\n");
traverse(FinalSuffs,disp);




return 0;

}
