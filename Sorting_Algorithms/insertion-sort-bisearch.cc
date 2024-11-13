/**
 *  \file insertion-sort-bisearch.cc
 *
 *  \brief Implement your insertion sort with binary search in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

int binarySearch(int key, keytype* A, int low, int high){
  if(high <= low){
    return (key > A[low]) ? (low + 1) : low;
  }
  int mid = (low + high)/2;
  if(key == A[mid]){
    return mid +1;
  }
  if(key > A[mid]){
    return binarySearch(key, A, mid+1,high);
  }
  return binarySearch(key, A, low, mid-1);

}
void mySort (int N, keytype* A){
  if(N==1) return;
  int i,j, place, k, targeted;
  for(i = 1; i < N; ++i){
    j = i - 1;
    targeted = A[i];

    place = binarySearch(targeted, A, 0, j);

    while(j >= place){
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = targeted;
  }
}

/* eof */
