/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

void merge(int N_L, keytype* A_L, int N_R, keytype *A_R){
  int i = 0;
  int j = 0;
  int k = 0;
  keytype* mergedArray = (keytype*)malloc(sizeof(keytype) * (N_L + N_R));
  while(i < N_L && j < N_R){ //set the conditions for the while-loop 
    if(A_L[i] < A_R[j]){
      mergedArray[k] = A_L[i]; //check if the left element is less than right element, increment i if so
      i++;
    }
    else{
      mergedArray[k] = A_R[j]; //if not less than, element is in the correct position increment j
      j++;
    }
    k++;
  }
  if(i < N_L){
    for(; i < N_L; i++){
     mergedArray[k] = A_L[i]; //if the left over elements in the left array arent sorted then input them
     k++;
    }
  }
  else if(j < N_R){ //if the left over elements in the right array arent sorted then place them merged array
    for(;j < N_R; j++){
     mergedArray[k] = A_R[j];
     k++;
    }
  }
  for (int i = 0; i < N_L + N_R; i++) {
    A_L[i] = mergedArray[i]; 
  }
}
void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  if(N == 1) return;
  mySort(N/2, A);//left half of the array
  int is_odd = N % 2;
  if(is_odd > 0){ //check to see if the array is odd
    mySort((N/2)+1, (A+(N/2)));
    merge(N/2, A, (N/2)+1, A+(N/2)); //if odd then account for the extra element
  }
  else{
    mySort(N/2, A+(N/2));
    merge(N/2, A, (N/2), A+(N/2)); //proceed as normal if not odd
  }
}


/* eof */
