#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SLOTS 100

typedef struct
{
    int slots[MAX_SLOTS];
    int front;
    int rear;
    int count;
} Queue;

// Queue Operations
void initializeQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);

void enqueue(Queue *q, int slotNo);
int dequeue(Queue *q);

void displayAvailableSlots(Queue *q);

#endif

