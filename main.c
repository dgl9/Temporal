#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "create_buchi.h"


int main() {
  /* code */


  Read in from input
  Tadj =.....
  node TQ[] = {1,2,3,4,5,6,7,8,9};
  node Tx[] = {0, 0, 4, 6, 8, 8, 8, 4, 10};
  node Ty[] = {0, 4, 4, 4, 4, 1.8, 0, 0, 1.8};

  int r = 0.2


  ... plot the stuff ....
  int maxNum=ListLength(TQ);
  int BigNum = 1000000;


  [minDist,IndexMinDist,Dist] = DistanceMatrix(TQ,Tx,Ty,BigNum); TRANSLATE

  int N = 9;
  int x0[] = {1, 2, 3, 4, 5, 6, 7, 8, 1}

  int d = 2*N;

  %--------Buchi Automaton--------
  int N_p = 7;
  node ** x;
  FILE *stream;
  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int sn_count = getStateNames(stream, BUCH_AUT, STATE_NAMES);
  x = create_buchi(x);
  printf("%i\n", sn_count);
  callback disp = display;

  NEIGHBOR MATRIX.... TRANSLATE

  node * states;
  int numOfBuchiEdges=length(find(~cellfun(@isempty,B1.trans))) TRANSLATE

  %--------Label AP graph--------




  cell_matrix * AP = newCellMatrix(N_p,N+2);
  int num = -100;

  AP(:,:)={num}; initialize all of the cells to a number
  for(int i = 0; i < N_ap;i++ ){
    setCell(AP,i,N+1,pow(2,i));
  }


  setCell(AP,1,1,5);
  setCell(AP,1,2,5);
  setCell(AP,1,3,5);

  ....


  int nMaxPre = 1000;
  n = length->cols * maxNum * N

  node * parent;   %parent of n-th sample
  matrix * Qpba = newMatrix(nMaxPre,N+1);     % matrix of vertices, N+1 refers to the buchi state
  Qpba(1,:) = [x0,B1.S0]; TRANSLATE CREATE FILL IN MATRIX
  node * path;
  float epsilon = 0.1;  %threshold for satisfying AP
  int ind = 2;%points at the next available (empty) entry of Qpba
  int stop=0;
  matrix * CostNode=newMatrix(nMaxPre,1);
  matrix * SizeTree=newMatrix(nMaxPre,1);

  %==================Build Prefix part========================================

  int * goal = B1.F; MAYBE APPEND LIST
  node * F;
  matrix * reject = zeros(1,nMaxPre);
  int sample = 0;
  matrix * rejectExist=zeros(1,nMaxPre);
  matrix * rejectInf=zeros(1,nMaxPre);

  int f = 1;
  MeasureTime
  for(int n = 0, i < nMaxPre-1; i++){
    [xNew,pickInd]=sampleReachablePTSpointTree(Qpba,N,T,ind); TRANSLATE FUNCTION
    sat=observeInDiscreteEnvironment(N,N_p,AP,xNew,epsilon); TRANSLATE FUNCTION

    rejectExist[n]=0;
    for(int q2 = 0; q2 <= states->cols; q2++){
      qBnext=getElement(states,q2,1);
      candParents=find(neig(:,qBnext)>0);% TRANSLATE
      node * indices;
      for(int jj == 0; jj < candParents->cols; jj ++){
         node * qBPrev=getElement(candParents,jj,1);
         indices=[indices;find(Qpba(:,N+1)==qBPrev)]; TRANSLATE
      }
      if (ListLength(indices)>0){
        % Find the nearest node to xNew among all states in Qpba q=(?,qBprev):
        matrix * Qpts = Qpba(indices,1:N);
        matrix * Qb = Qpba(indices,N+1);
        %Given qNext=(xNew,qBnext), we have to determine: qPrev=(xPrev(?), qBPrev(?)):
        %[xPrev,indexQpts]=findPrevPTSpoint(Qpts,xNew,Dist,BigNum);%indexQpts points at the indexQpts-th state of subspace [Qpts,Qb]
        [xPrev,indexQpts]=findPrevPTSpoint_star_V2(Qpts,Qb,Qpba,xNew,qBnext,Dist,BigNum,parent,B1,AP,N_p,epsilon);TRANSLATE FUNCTION
        qBPrev=Qb(indexQpts); TRANSLATE
        qPrev=[xPrev,qBPrev]; TRANSLATE
        indexSample=ismemberLocs([xNew,qBnext],Qpba, 'rows');%check if this node already exists in the tree
        if((indexSample==0) && (ListLength(qPrev)!=0)){
          % fprintf('accept1\n')
          sat=observeInDiscreteEnvironment(N,N_p,AP,xNew,epsilon); TRANSLATE FUNCTION
          if(~isempty(find(sum(sat)==B1.trans{qBPrev,qBnext}, 1)) %&& ~isempty(xPrev)){ %if there is a transition in PBA
              %    fprintf('accept2\n')
              %if(sum((xPrev-xNew))~=0 || abs(qBPrev-qBnext)>0.01){
                Qpba(ind,:) = [xNew,qBnext];
                indexInQpba=ismemberLocs(qPrev,Qpba, 'rows'); TRANSLATE ISMEMBERLOCATIONS
                parent(ind)=indexInQpba; CostPar=CostNode(indexInQpba);
                %CostNode(ind)=DistrCostOfTreeNode_MinCom(Qpba,CostPar,qPrev, ind,Dist);%CostOfTreeNode(Qpba,parent,ind,Dist);
                % NumOfSamples=ind;
                %[parent,CostNode]=Rewire_v2(ind,Qpba,CostNode,parent,BigNum,neig,Dist,B1,AP,N_p,epsilon,NumOfSamples);
                %uncomment next line to rewire
                [parent,CostNode]=Rewire_fast_v3(ind,Qpba,CostNode,parent,BigNum,neig,Dist,B1,AP,N_p,epsilon);
                %parent=parent1;CostNode=CostNode1
                ind = ind+1;
                if (mod(ind,1000)==0){
                    n
                    fprintf('sample number: %i\n', ind)
                }
                %flag=GoalSet(Qpba(ind-1,N+1),goal);
                if(~isempty(intersect(goal,Qpba(ind-1,N+1)))%flag%Goal(xNew)){
                    fprintf('The goal set reached!\n')
                    stop=1;
                    F=[F;ind-1];
                    %if length(F)==1
                    timeSol(f)=toc+timeS;
                    costPre(f)=min(CostNode(F));
                    f=f+1;
                    %indSol=ind-1;
                    %end
                    %break
                }
              }
            else{
                rejectInf(n)=rejectInf(n)+1;
            }
              else if(indexSample>0){ %rewire
                [parent,CostNode]=Rewire_fast_v3(indexSample,Qpba,CostNode,parent,BigNum,neig,Dist,B1,AP,N_p,epsilon); TRANSLATE FUNCTION
              }
          }

        }



      %======================Build suffix=======================================
      %toc
      SizeTree(n)=ind;
      end
      timepre=toc
      location=GenerateLocations4Samples(Qpba);
}


  }

  return 0;

}
