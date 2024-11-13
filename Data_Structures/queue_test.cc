#include "queue.cc"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer.c"

int main(int argc, char* argv[]){
    int N, T;
    long double total_time = 0.0L, avg_time = 0.0L;

    if (argc == 3) {
        N = atoi(argv[1]);
        T = atoi(argv[2]);
        assert (N > 0);
        assert (T > 0);
    }
    stopwatch_init();
    struct stopwatch_t* timer = stopwatch_create(); assert(timer);

    // create a queue
    Queue q(N);
    float x;
    for(int i = 0; i < T; i++){
        stopwatch_start(timer);
        x = q.dequeue();
        q.enqueue(x);
        total_time += stopwatch_stop(timer);
    } 
    stopwatch_destroy(timer);
    avg_time = (total_time / T);
    printf("Average Time: %Lg seconds", avg_time);
    return 0;
}