#include "dlist.cc"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include "timer.c"
#include "time.h"

int main(int argc, char* argv[]){
    int N, T;
    long double total_time = 0.0L, avg_time = 0.0L;
    if (argc == 2) {
        N = atoi(argv[1]);
        //T = atoi(argv[2]);
        assert (N > 0);
        //assert (T > 0);
    }
    stopwatch_init();
    struct stopwatch_t* timer = stopwatch_create(); assert(timer);

    // create a linked list
    DList dll;
    for(int i = 1; i < N; i++){
        dll.add_to_back(i);
    } 
    srand(time(NULL));
    int randomNum;
    for(int i = 0; i < N; i++){
        randomNum = 1+(rand() % N);
        stopwatch_start(timer);
        dll.search_value(randomNum);
        dll.remove(dll.search_value(randomNum));
        total_time += stopwatch_stop(timer);
        dll.add_to_front(randomNum);
    }
    avg_time = (total_time / N);
    printf("Time: %Lg", avg_time);
    return 0;
}