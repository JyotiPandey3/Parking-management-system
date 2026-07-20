#include <stdio.h>
#include "queue.h"

// Initialize Queue


void initializeQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
    q->count = 0;

    for(int i=1;i<=MAX_SLOTS;i++)
        enqueue(q,i);
}

int isEmpty(Queue *q)
{
    return q->count==0;
}

int isFull(Queue *q)
{
    return q->count==MAX_SLOTS;
}

void enqueue(Queue *q,int slotNo)
{
    if(isFull(q))
    {
        printf("\nQueue Overflow\n");
        return;
    }

    q->rear=(q->rear+1)%MAX_SLOTS;
    q->slots[q->rear]=slotNo;
    q->count++;
}

int dequeue(Queue *q)
{
    if(isEmpty(q))
        return -1;

    int slot=q->slots[q->front];

    q->front=(q->front+1)%MAX_SLOTS;
    q->count--;

    return slot;
}

void displayAvailableSlots(Queue *q)
{
    if(isEmpty(q))
    {
        printf("\nNo Slots Available\n");
        return;
    }

    printf("\nAvailable Slots:\n");

    int index=q->front;

    for(int i=0;i<q->count;i++)
    {
        printf("%d ",q->slots[index]);
        index=(index+1)%MAX_SLOTS;
    }

    printf("\n");
}
