/**
 *  \file insertion-sort.cc
 *
 *  \brief Implement your insertion sort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  int key; //define key
  int i; //define i
  for(int j = 1; j < N; j++){ //loop through array
    key = A[j];
    i = j - 1;
    while(i >= 0 && A[i] > key){ //check to see if the key is in the right position
      A[i+1] = A[i];
      i = i - 1;
    }
    A[i + 1] = key;
  }

}

/* eof */
