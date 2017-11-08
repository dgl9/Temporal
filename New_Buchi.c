#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "library.h"
int getStateNamesNew(FILE * stream, char * BUCH_AUT, char ** STATE_NAMES);
int on_off(char * line, int curr);
Buchi * Buchi_Struct_New();
int which_state_start(char * line, int curr);
int which_state_end(char * line, char ** state_names, int sn_count);
node * intersection(node * A, node * B);
node * power_set_indList(char * token, char ** power_set, int N_ap);
node * ListUnion(node * A, node * B);
node * loopIntersect(char * line, node * curr_list, char ** power_set, int N_ap);

int main() {
  callback disp = display;
  int N_p = 7;
  Buchi * B1;
  FILE *stream;
  char BUCH_AUT[100000];
  char* STATE_NAMES[50];
  int sn_count = getStateNamesNew(stream, BUCH_AUT, STATE_NAMES);
  int N_ap = 7;
  char * alphabet[N_ap];
  char * power_set[(int)(pow(2,N_ap))];
  getAlpha(alphabet, N_ap);
  getPowerSet(power_set,alphabet,N_ap);
  for(int i = 0; i < 7; i++){
      printf("%s\n", alphabet[i]);
  }
  for(int i = 0; i < pow(2,N_ap); i++){
      printf("%s\n", power_set[i]);
  }
  printf("%i\n",sn_count);

  B1 = Buchi_Struct_New();
  node * z1 = power_set_indList("p1", power_set, 7);
  node * z2 = power_set_indList("p2", power_set, 7);
  node * z3 = power_set_indList("p3", power_set, 7);
  node * z4 = power_set_indList("p4", power_set, 7);
  node * z5 = intersection(z1,z2);

    traverse(z1,disp);
    printf("\n\n\n");
    traverse(z2,disp);
    printf("\n\n\n");
    traverse(z5,disp);
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");



  printCellMatrix(B1->Trans);

  traverse(B1->F,disp);
    printf("\n\n\n");
  traverse(B1->S,disp);
      printf("\n\n\n");
  traverse(B1->S0,disp);

  return 0;
}



Buchi * Buchi_Struct_New() {
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
  int print = 0;
  int state_start = 0;
  int state_end = 0;
  //----------------------------------------------------------
  while ((read2 = getline(&line2, &len2, stream2)) != -1) {
    if((print = on_off(line2,print))){
      state_start = which_state_start(line2,state_start);
      state_end = which_state_end(line2, STATE_NAMES, sn_count);
      if(state_end){
          CELL(B1->Trans,state_start, state_end) = loopIntersect(line2, CELL(B1->Trans,state_start, state_end),power_set,N_ap);
      }
      else{
        if(strstr(line2,"init")){
          B1->S0 = append(B1->S0,state_start);
        }
        if(strstr(line2,"accept")){
          B1->F = append(B1->F,state_start);
        }
      }

    }

  }
  printCellMatrix(B1->Trans);
  return B1;
}




node * loopIntersect(char * line, node * curr_list, char ** power_set, int N_ap){
  node * line_list = NULL;
  node * full_set = NULL;
  for(int i = 1; i < pow(2,N_ap); i++){
    full_set = append(full_set, i );
  }
  callback disp = display;
  int all_done = 0;
  int count = 0;
  char * token;
  while(!all_done){
    if(!count){
      token = strtok(line, " & ");
    }
    else{
      token = strtok(NULL, " & ");
    }
    if(strstr(token, "{")){
      all_done = 1;
    }
    token[2] = '\0';
    printf("%s\n", token);
    if(token[0]!='p'){
      line_list = intersection(line_list, full_set);
    }
    else{
      line_list = intersection(line_list,power_set_indList(token,power_set,N_ap));
    }

    count++;
  }
  if(!curr_list){
    return line_list;
  }
  return ListUnion(curr_list,line_list);

}



node * intersection(node * A, node * B){
  if(!A){
    return B;
  }
  if(!B){
    return A;
  }
  node * new = NULL;
  node * temp = A;
  int aLen = ListLength(A);
  for(int i = 0; i < aLen; i++){
    if(search(B,temp->data)){
      new = append(new, temp->data);
    }
    temp = temp->next;
  }
  return new;
}


node * ListUnion(node * A, node * B){
  if(!A){
    return B;
  }
  if(!B){
    return A;
  }
  node * new = NULL;
  node * temp = A;
  int aLen = ListLength(A);
  int bLen = ListLength(B);
  for(int i = 0; i < aLen; i++){
    new = append(new, temp->data);
    temp = temp->next;
  }
  temp = B;
  for(int i = 0; i < bLen; i++){
    if(!search(new, temp->data)){
      new = append(new, temp->data);
    }
    temp = temp->next;
  }
  return new;
}



node * power_set_indList(char * token, char ** power_set, int N_ap){
  node * set = NULL;
  for(int i = 0; i < (int)pow(2,N_ap); i++){
    if(strstr(power_set[i], token)){
      set = append(set,i);
    }
  }
  return set;
}



int which_state_start(char * line, int curr){
  if(strstr(line,"state")){
    return curr + 1;
  }
  return curr;

}
int which_state_end(char * line, char ** state_names, int sn_count){
  char * end_state = strstr(line, "->");
  if(end_state){
    end_state = end_state+3;

    for(int i = 1; i <= sn_count; i++){
      if (strstr(state_names[i-1],end_state)){
        printf("%i  %s\n",  i, state_names[i-1]);
        return i;
      }
    }
  }
  return 0;
}


int on_off(char * line, int curr){
  if(strstr(line,"Buchi automaton after simplification")!= NULL & line[0] == 'B' & curr == 0){
    return 1;
  }
  if(strstr(line,"never {")!= NULL){
    return 0;
  }
  else{
    return curr;
  }
}





int getStateNamesNew(FILE * stream, char * BUCH_AUT, char ** STATE_NAMES){

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
      strncpy(&BUCH_AUT[prev_len], line, read);
      prev_len += read;
      if(strstr(line, "state")!=NULL){
        STATE_NAMES[sn_count] = (char *)malloc(read*sizeof(char));
        strncpy(STATE_NAMES[sn_count], &line[6],read-6);
        sn_count++;
      }
    }
  }
  free(line);
  fclose(stream);
  return sn_count;
}
