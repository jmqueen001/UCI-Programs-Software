#include "queue.h"


Queue::Queue(int size)
{
    arr = new int[size];
    capacity = size;
    head = 0;
    tail = -1;
    count = 0;
}


//Dequeue the front element
float Queue::dequeue()
{
    float x = arr[head];
    head = (head + 1);
    count--;
 
    return x;
}
 
//Enqueue an item to the queue
void Queue::enqueue(float value)
{
    tail = (tail + 1) % capacity;
    arr[tail] = value;
    count++;
}

Queue:: ~Queue()
{
    delete[] arr;
}