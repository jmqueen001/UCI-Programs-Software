#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
  public:
  /* implement copy constructor, assignment, destructor if needed */
  Queue(int size);
  void enqueue(float value);
  float dequeue();
  ~Queue();

  private:
  /* declare your data */
    int *arr;       // array to store queue elements
    int capacity;   // maximum capacity of the queue
    int head;      // head points to the first element in the queue
    int tail;       // tail points to the last element in the queue
    int count;      // current size of the queue 
};


#endif
